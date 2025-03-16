#include <iostream>
#include <dlfcn.h>
#include <memory>
#include <map>
#include <mutex>

// 自定义删除器
auto dl_deleter = [](void* handle) {
    if (handle) {
        dlclose(handle);
        std::cout << "Library unloaded\n";
    }
};

// 缓存类型定义
using LibraryHandle = std::shared_ptr<void>;
using WeakHandle = std::weak_ptr<void>;
using CacheMap = std::map<std::string, WeakHandle>;

// 全局缓存及互斥锁（线程安全）
static CacheMap lib_cache;
static std::mutex cache_mutex;

// 带缓存的库加载函数
LibraryHandle load_library(const std::string& path) {
    std::lock_guard<std::mutex> lock(cache_mutex);

    // 尝试从缓存获取
    if (auto it = lib_cache.find(path); it != lib_cache.end()) {
        if (auto handle = it->second.lock()) {
            std::cout << "Using cached library: " << path << "\n";
            return handle;
        }
    }

    // 加载新库
    void* raw_handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!raw_handle) {
        throw std::runtime_error(dlerror());
    }

    // 创建智能指针
    LibraryHandle handle(raw_handle, dl_deleter);
    
    // 更新缓存
    lib_cache[path] = handle;
    std::cout << "New library loaded: " << path << "\n";
    return handle;
}

// 获取函数指针的模板函数
template <typename FuncType>
FuncType get_function(const LibraryHandle& handle, const char* name) {
    dlerror(); // 清除旧错误
    auto func = reinterpret_cast<FuncType>(dlsym(handle.get(), name));
    if (const char* err = dlerror()) {
        throw std::runtime_error(err);
    }
    return func;
}

int main() {
    try {
        // 第一次加载（新加载）
        auto handle1 = load_library("./libmylib.so");
        using hello_t = void(*)();
        auto hello = get_function<hello_t>(handle1, "hello");
        hello();

        // 第二次加载（使用缓存）
        auto handle2 = load_library("./libmylib.so");
        using add_t = int(*)(int, int);
        auto add = get_function<add_t>(handle2, "add");
        std::cout << "3 + 5 = " << add(3, 5) << std::endl;

        // 测试缓存失效
        {
            auto temp_handle = load_library("./libmylib.so");
        } // 此处临时句柄释放，但缓存仍存在weak_ptr

        // 第三次加载（缓存仍有效）
        auto handle3 = load_library("./libmylib.so");
        std::cout << "7 + 2 = " << add(7, 2) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}