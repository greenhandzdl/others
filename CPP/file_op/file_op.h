#ifndef FILE_OP_H
#define FILE_OP_H

#include <string>
#include <cstdint>

// 菜单选项枚举类
enum class MenuOptions {
    EXIT = 1,
    MAKE_FILE,
    READ_FILE,
    WRITE_FILE,
    MAKE_BINARY_FILE,
    READ_BINARY_FILE,
    WRITE_BINARY_FILE,
    SEEK_BINARY_FILE
};

// 常量定义
const int CHAR_ARRAY_MAX = 20;

// 数据记录结构体
struct DataRecord {
    int32_t id;         // 使用int32_t确保在不同平台上大小一致
    double value;       // 双精度浮点数
    char name[CHAR_ARRAY_MAX];      // 固定大小的字符数组
};

// 菜单相关函数
bool menu(MenuOptions& choice) noexcept;
bool filename_get(std::string& filename) noexcept;

// 基本文件操作函数
bool file_make(std::string&& filename) noexcept;
bool file_make(const std::string& filename) noexcept;
bool file_read(std::string&& filename) noexcept;
bool file_read(const std::string& filename) noexcept;
bool file_write(std::string&& filename) noexcept;
bool file_write(const std::string& filename) noexcept;

// 二进制文件操作函数
bool file_make_binary(std::string&& filename) noexcept;
bool file_make_binary(const std::string& filename) noexcept;
bool file_read_binary(std::string&& filename) noexcept;
bool file_read_binary(const std::string& filename) noexcept;
bool file_write_binary(std::string&& filename) noexcept;
bool file_write_binary(const std::string& filename) noexcept;
bool file_seek_binary(std::string&& filename) noexcept;
bool file_seek_binary(const std::string& filename) noexcept;

// 结构体二进制操作函数
bool file_write_struct_binary(std::string&& filename) noexcept;
bool file_write_struct_binary(const std::string& filename) noexcept;
bool file_read_struct_binary(std::string&& filename) noexcept;
bool file_read_struct_binary(const std::string& filename) noexcept;

// 工具函数
std::string add_dat_extension(const std::string& filename) noexcept;

#endif // FILE_OP_H