// main.cpp
#include <iostream>
#include <dlfcn.h>
#include <memory>
#include <map>
#include <mutex>
#include <chrono>
#include <thread>
#include <atomic>

//------------------------ 核心缓存系统 ------------------------//
class LibraryCache {
private:
    struct CacheEntry {
        std::unique_ptr<void, decltype(&dlclose)> unique_handle;
        std::weak_ptr<void> weak_handle;
        std::chrono::steady_clock::time_point last_access;
    };

    std::map<std::string, CacheEntry> cache_;
    std::mutex mutex_;
    std::atomic<bool> cleaner_running_{true};
    const std::chrono::seconds cleanup_interval_{30};

    // 自定义删除器（需通过unique_ptr管理）
    static void HandleDeleter(void* handle) {
        if (handle) {
            dlclose(handle);
            std::cout << "\n[Cache] Library unloaded\n";
        }
    }

public:
    LibraryCache() {
        // 启动独立清理线程
        std::thread([this] {
            while (cleaner_running_) {
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

        // 现有缓存检查
        if (auto it = cache_.find(path); it != cache_.end()) {
            if (auto sptr = it->second.weak_handle.lock()) {
                it->second.last_access = std::chrono::steady_clock::now();
                std::cout << "[Cache] Using cached: " << path << "\n";
                return sptr;
            }
        }

        // 新加载库
        void* raw = dlopen(path.c_str(), RTLD_LAZY);
        if (!raw) throw std::runtime_error(dlerror());

        // 创建双重指针结构
        auto unique = std::unique_ptr<void, decltype(&dlclose)>(raw, HandleDeleter);
        auto shared = std::shared_ptr<void>(unique.get(), [](void*){ /* 空删除器 */ });

        // 更新缓存
        cache_[path] = {
            std::move(unique),  // 转移所有权
            shared,             // weak_ptr观察
            std::chrono::steady_clock::now()
        };

        std::cout << "[Cache] New loaded: " << path << "\n";
        return shared;
    }

    void clean_expired() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto now = std::chrono::steady_clock::now();

        for (auto it = cache_.begin(); it != cache_.end();) {
            bool expired = it->second.weak_handle.expired();
            bool timeout = (now - it->second.last_access) > std::chrono::minutes(5);

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

//--------------------- 全局缓存实例 ---------------------//
LibraryCache global_cache;

//--------------------- 函数获取模板 ---------------------//
template <typename FuncType>
FuncType get_func(const std::shared_ptr<void>& handle, const char* name) {
    dlerror();
    auto func = reinterpret_cast<FuncType>(dlsym(handle.get(), name));
    if (const char* err = dlerror()) {
        throw std::runtime_error(err);
    }
    return func;
}

//--------------------- 示例用法 ---------------------//
int main() {
    try {
        // 第一次加载
        auto lib1 = global_cache.load("./libmylib.so");
        auto hello = get_func<void()>(lib1, "hello");
        hello();

        // 第二次加载（缓存）
        auto lib2 = global_cache.load("./libmylib.so");
        auto add = get_func<int(int,int)>(lib2, "add");
        std::cout << "3+5 = " << add(3,5) << "\n";

        // 手动触发清理
        std::cout << "\nTrigger manual cleaning:\n";
        global_cache.clean_expired();

        // 强制过期测试
        {
            auto temp = global_cache.load("./libmylib.so");
        } // 退出作用域，但缓存仍保留unique_ptr

        std::cout << "\nAfter scope exit:\n";
        auto lib3 = global_cache.load("./libmylib.so"); // 仍然命中缓存
        std::cout << "7+2 = " << add(7,2) << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}