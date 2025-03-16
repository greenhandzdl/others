// main.cpp
#include <iostream>
#include <dlfcn.h>
#include <memory>
#include <map>
#include <mutex>
#include <chrono>
#include <thread>
#include <atomic>

class LibraryCache {
private:
    struct CacheEntry {
        std::unique_ptr<void, int(*)(void*)noexcept> unique_handle;
        std::weak_ptr<void> weak_handle;
        std::chrono::steady_clock::time_point last_access;

        CacheEntry(std::unique_ptr<void, int(*)(void*)noexcept>&& uh,
                  std::weak_ptr<void> wh,
                  std::chrono::steady_clock::time_point la)
            : unique_handle(std::move(uh)),
              weak_handle(wh),
              last_access(la) {}
    };

    std::map<std::string, CacheEntry> cache_;
    std::mutex mutex_;
    std::atomic<bool> cleaner_running_{true};
    const std::chrono::seconds cleanup_interval_{5};

public:
    LibraryCache() {
        std::thread([this] {
            while (cleaner_running_.load()) {
                std::this_thread::sleep_for(cleanup_interval_);
                clean_expired();
            }
        }).detach();
    }

    ~LibraryCache() {
        cleaner_running_ = false;
    }

    std::shared_ptr<void> load(const std::string& path) {
        std::lock_guard<std::mutex> lock(mutex_);

        // 检查现有缓存
        if (auto it = cache_.find(path); it != cache_.end()) {
            if (auto sptr = it->second.weak_handle.lock()) {
                it->second.last_access = std::chrono::steady_clock::now();
                std::cout << "[Cache] Using cached: " << path << "\n";
                return sptr;
            }
        }

        // 加载新库
        void* raw = dlopen(path.c_str(), RTLD_LAZY);
        if (!raw) throw std::runtime_error(dlerror());

        // 创建符合dlclose签名的删除器
        auto deleter = [](void* h) noexcept -> int {
            return h ? dlclose(h) : 0;
        };

        // 构造unique_ptr（所有权持有者）
        std::unique_ptr<void, int(*)(void*)noexcept> unique(raw, deleter);
        
        // 创建shared_ptr（观察者，不实际管理资源）
        auto shared = std::shared_ptr<void>(
            unique.release(),  // 转移所有权
            [](void*){}        // 空删除器
        );

        // 插入缓存条目
        cache_.try_emplace(
            path,
            std::move(unique),            // unique_ptr转移进map
            std::weak_ptr<void>(shared),  // 创建weak_ptr观察
            std::chrono::steady_clock::now()
        );

        std::cout << "[Cache] New loaded: " << path << "\n";
        return shared;
    }

    void clean_expired() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto now = std::chrono::steady_clock::now();

        for (auto it = cache_.begin(); it != cache_.end();) {
            bool expired = it->second.weak_handle.expired();
            bool timeout = (now - it->second.last_access) > std::chrono::seconds(30);

            if (expired || timeout) {
                std::cout << "[Cache] Clean: " << it->first 
                          << (expired ? " (expired)" : " (timeout)") << "\n";
                it = cache_.erase(it);
            } else {
                ++it;
            }
        }
    }
};

// 全局缓存实例
LibraryCache global_cache;

// 函数指针获取模板
template <typename FuncPtr>
FuncPtr get_func(const std::shared_ptr<void>& handle, const char* name) {
    dlerror(); // 清除旧错误
    auto func = reinterpret_cast<FuncPtr>(dlsym(handle.get(), name));
    if (const char* err = dlerror()) {
        throw std::runtime_error(err);
    }
    return func;
}

// 动态库函数类型声明
using hello_t = void(*)();
using add_t = int(*)(int, int);

int main() {
    try {
        // 第一次加载
        auto lib1 = global_cache.load("./libmylib.so");
        auto hello = get_func<hello_t>(lib1, "hello");
        hello();

        // 第二次加载（使用缓存）
        auto lib2 = global_cache.load("./libmylib.so");
        auto add = get_func<add_t>(lib2, "add");
        std::cout << "3 + 5 = " << add(3, 5) << "\n";

        // 测试缓存失效
        {
            auto temp = global_cache.load("./libmylib.so");
        }

        // 第三次加载（缓存仍有效）
        auto lib3 = global_cache.load("./libmylib.so");
        std::cout << "7 + 2 = " << add(7, 2) << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}