// main.cpp
#include <iostream>
#include <dlfcn.h>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <chrono>
#include <thread>
#include <atomic>
#include <functional>

class LibraryCache {
private:
    struct CacheEntry {
        std::weak_ptr<void> weak_handle;
        std::chrono::steady_clock::time_point last_access;
    };

    std::unordered_map<std::string, CacheEntry> cache_;
    std::mutex mutex_;
    std::atomic<bool> cleaner_running_{true};
    const std::chrono::seconds cleanup_interval_{5};

    // 自定义删除器
    static void HandleDeleter(void* handle) {
        if (handle) {
            dlclose(handle);
            std::cout << "[Cache] Library unloaded\n";
        }
    }

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

        // 使用结构化绑定遍历查找
        bool found = false;
        for (auto& [key, entry] : cache_) {
            if (key == path) {
                found = true;
                if (auto sptr = entry.weak_handle.lock()) {
                    entry.last_access = std::chrono::steady_clock::now();
                    std::cout << "[Cache] Using cached: " << path << "\n";
                    return sptr;
                }
                break;
            }
        }

        // 加载新库
        void* raw = dlopen(path.c_str(), RTLD_LAZY);
        if (!raw) throw std::runtime_error(dlerror());

        // 直接使用shared_ptr管理资源
        auto shared = std::shared_ptr<void>(
            raw, 
            [](void* h) {
                HandleDeleter(h);
            }
        );

        // 更新缓存
        cache_[path] = {
            std::weak_ptr<void>(shared),
            std::chrono::steady_clock::now()
        };

        std::cout << "[Cache] New loaded: " << path << "\n";
        return shared;
    }

    void clean_expired() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto now = std::chrono::steady_clock::now();

        // 使用现代遍历语法
        for (auto it = cache_.begin(); it != cache_.end();) {
            const auto& [path, entry] = *it;
            
            bool need_remove = 
                entry.weak_handle.expired() || 
                (now - entry.last_access) > std::chrono::seconds(30);

            if (need_remove) {
                std::cout << "[Cache] Clean: " << path
                          << (entry.weak_handle.expired() ? " (expired)" : " (timeout)")
                          << "\n";
                it = cache_.erase(it);
            } else {
                ++it;
            }
        }
    }
};

// 全局缓存实例
LibraryCache global_cache;

// 改进的函数指针获取模板
template <typename FuncType>
FuncType get_function(const std::shared_ptr<void>& lib, const char* name) {
    dlerror();
    auto func = reinterpret_cast<FuncType>(dlsym(lib.get(), name));
    if (const char* err = dlerror()) {
        throw std::runtime_error("Symbol not found: " + std::string(name));
    }
    return func;
}

// 使用示例
int main() {
    try {
        // 定义函数类型
        using HelloFunc = void(*)();
        using AddFunc = int(*)(int, int);

        // 第一次加载
        auto lib1 = global_cache.load("./libmylib.so");
        auto hello = get_function<HelloFunc>(lib1, "hello");
        hello();

        // 第二次加载（命中缓存）
        auto lib2 = global_cache.load("./libmylib.so");
        auto add = get_function<AddFunc>(lib2, "add");
        std::cout << "3 + 5 = " << add(3, 5) << "\n";

        // 测试缓存过期
        {
            auto temp = global_cache.load("./libmylib.so");
        }

        // 第三次加载（仍然有效）
        auto lib3 = global_cache.load("./libmylib.so");
        std::cout << "7 + 2 = " << add(7, 2) << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

// g++ main.cpp -o main -ldl