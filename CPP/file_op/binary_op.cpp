#include "file_op.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <cstring>

// 设置本地化支持中文的函数
void set_utf8_locale() noexcept {
    using namespace std;
    setlocale(LC_ALL, "zh_CN.UTF-8");
    locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
    wcin.imbue(utf8_locale);
    wcout.imbue(utf8_locale);
    wcerr.imbue(utf8_locale);
    wclog.imbue(utf8_locale);
}

// 添加.dat扩展名的函数，不会修改原始字符串，不会抛出异常
std::string add_dat_extension(const std::string& filename) noexcept {
    if (filename.size() >= 4 && 
        filename.substr(filename.size() - 4) == ".dat") {
        return filename;
    }
    return filename + ".dat";
}

// 使用右值引用和完美转发的版本
bool file_make_binary(std::string&& filename) noexcept {
    using namespace std;
    set_utf8_locale(); // 设置UTF-8编码环境
    string binary_filename = add_dat_extension(std::move(filename));
    ofstream file(binary_filename.c_str(), ios_base::out|ios_base::binary|ios_base::trunc);
    if(!file.is_open()) {
        wcerr << L"文件打开失败" << endl;
        return false;
    }
    file.close();
    file.clear();
    return true;
}

// 左值引用重载版本，转发到右值引用版本
bool file_make_binary(const std::string& filename) noexcept {
    return file_make_binary(std::string(filename));
}

// 使用右值引用和完美转发的版本
bool file_read_binary(std::string&& filename) noexcept {
    using namespace std;
    set_utf8_locale(); // 设置UTF-8编码环境
    string binary_filename = add_dat_extension(std::move(filename));
    ifstream file(binary_filename.c_str(), ios_base::in|ios_base::binary);
    if(!file.is_open()) {
        wcerr << L"文件打开失败" << endl;
        return false;
    }
    
    file.seekg(0, ios::end);
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);
    
    size_t record_count = size / sizeof(DataRecord);
    wcout << L"文件中包含 " << record_count << L" 个结构体记录" << endl;
    
    if(record_count == 0) {
        wcout << L"文件为空，没有结构体数据" << endl;
        file.close();
        return true;
    }
    
    DataRecord record;
    cout << left << setw(10) << "ID" << setw(15) << "值" << "名称" << endl;
    cout << setfill('-') << setw(40) << "-" << setfill(' ') << endl;
    
    for(size_t i = 0; i < record_count; i++) {
        file.read(reinterpret_cast<char*>(&record), sizeof(DataRecord));
        
        if(file.gcount() == sizeof(DataRecord)) {
            cout << left << setw(10) << record.id 
                 << setw(15) << record.value 
                 << record.name << endl;
        }
    }
    
    file.close();
    file.clear();
    return true;
}

// 左值引用重载版本，转发到右值引用版本
bool file_read_binary(const std::string& filename) noexcept {
    return file_read_binary(std::string(filename));
}

// 使用右值引用和完美转发的版本
bool file_write_binary(std::string&& filename) noexcept {
    using namespace std;
    set_utf8_locale(); // 设置UTF-8编码环境
    string binary_filename = add_dat_extension(std::move(filename));
    ofstream file(binary_filename.c_str(), ios_base::out|ios_base::binary|ios_base::app);
    if(!file.is_open()) {
        wcerr << L"文件打开失败" << endl;
        return false;
    }
    
    DataRecord record;
    
    wcout << L"请输入ID (整数): ";
    wcin >> record.id;
    wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
    
    wcout << L"请输入数值 (浮点数): ";
    wcin >> record.value;
    wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
    
    wcout << L"请输入名称 (最多19个字符): ";
    wcout.flush(); // 确保提示立即显示
    // 使用wstring临时存储宽字符输入
    wstring wname;
    getline(wcin, wname);
    
    // 添加反馈信息
    wcout << L"名称已输入: " << wname << endl;
    
    // 转换为窄字符串并复制到record.name
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    string name = converter.to_bytes(wname);
    strncpy(record.name, name.c_str(), CHAR_ARRAY_MAX - 1);
    record.name[CHAR_ARRAY_MAX - 1] = '\0'; // 确保字符串以null结尾
    
    file.write(reinterpret_cast<const char*>(&record), sizeof(DataRecord));
    
    cout << "结构体数据已写入" << endl;
    
    file.close();
    file.clear();
    return true;
}

// 左值引用重载版本，转发到右值引用版本
bool file_write_binary(const std::string& filename) noexcept {
    return file_write_binary(std::string(filename));
}

// 使用右值引用和完美转发的版本
bool file_seek_binary(std::string&& filename) noexcept {
    using namespace std;
    set_utf8_locale(); // 设置UTF-8编码环境
    string binary_filename = add_dat_extension(std::move(filename));
    fstream file(binary_filename.c_str(), ios_base::in|ios_base::out|ios_base::binary);
    if(!file.is_open()) {
        wcerr << L"文件打开失败" << endl;
        return false;
    }
    
    file.seekg(0, ios::end);
    streamsize file_size = file.tellg();
    file.seekg(0, ios::beg);
    
    size_t record_count = file_size / sizeof(DataRecord);
    wcout << L"文件中包含 " << record_count << L" 个结构体记录" << endl;
    
    if(record_count == 0) {
        wcout << L"文件为空，没有结构体数据" << endl;
        file.close();
        return true;
    }
    
    wcout << L"请选择操作:" << endl;
    wcout << L"1. 读取指定位置的结构体" << endl;
    wcout << L"2. 修改指定位置的结构体" << endl;
    
    int op_choice;
    wcin >> op_choice;
    
    if(op_choice != 1 && op_choice != 2) {
        wcout << L"无效的选择" << endl;
        file.close();
        return false;
    }
    
    wcout << L"请输入要操作的结构体索引 (0-" << record_count - 1 << "): ";
    size_t record_index;
    wcin >> record_index;
    
    if(record_index >= record_count) {
        wcout << L"索引超出范围" << endl;
        file.close();
        return false;
    }
    
    // 定位到指定的结构体位置
    streampos record_pos = record_index * sizeof(DataRecord);
    
    if(op_choice == 1) { // 读取结构体
        // 确保文件指针正确定位到指定的结构体位置
        file.clear(); // 清除任何可能的错误标志
        file.seekg(record_pos, ios::beg);
        
        // 检查文件指针是否正确定位
        if(file.tellg() != record_pos) {
            wcout << L"文件指针定位失败，当前位置: " << file.tellg() << L", 期望位置: " << record_pos << endl;
            file.close();
            return false;
        }
        
        DataRecord record;
        file.read(reinterpret_cast<char*>(&record), sizeof(DataRecord));
        
        // 检查读取是否成功
        if(file.gcount() == sizeof(DataRecord)) {
            // 转换名称为宽字符串以正确显示中文
            wstring_convert<codecvt_utf8<wchar_t>> converter;
            wstring wname = converter.from_bytes(record.name);
            
            wcout << L"读取的结构体数据:" << endl;
            wcout << left << setw(10) << L"ID" << setw(15) << L"值" << L"名称" << endl;
            wcout << setfill(L'-') << setw(40) << L"-" << setfill(L' ') << endl;
            wcout << left << setw(10) << record.id 
                  << setw(15) << record.value 
                  << wname << endl;
        }
        else {
            wcout << L"读取结构体失败，实际读取字节数: " << file.gcount() << L", 期望字节数: " << sizeof(DataRecord) << endl;
        }
    }
    else { // 修改结构体
        file.clear(); // 清除任何可能的错误标志
        file.seekg(record_pos, ios::beg);
        DataRecord old_record;
        file.read(reinterpret_cast<char*>(&old_record), sizeof(DataRecord));
        
        if(file.gcount() != sizeof(DataRecord)) {
            wcout << L"读取原结构体失败，实际读取字节数: " << file.gcount() << L", 期望字节数: " << sizeof(DataRecord) << endl;
            file.close();
            return false;
        }
        
        // 转换名称为宽字符串以正确显示中文
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        wstring wname = converter.from_bytes(old_record.name);
        
        wcout << L"当前结构体数据:" << endl;
        wcout << left << setw(10) << L"ID" << setw(15) << L"值" << L"名称" << endl;
        wcout << setfill(L'-') << setw(40) << L"-" << setfill(L' ') << endl;
        wcout << left << setw(10) << old_record.id 
             << setw(15) << old_record.value 
             << wname << endl;
        
        wcout << L"请输入新的结构体数据:" << endl;
        DataRecord new_record;
        
        wcout << L"请输入ID (整数): ";
        wcin >> new_record.id;
        wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
        
        wcout << L"请输入数值 (浮点数): ";
        wcin >> new_record.value;
        wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
        
        wcout << L"请输入名称 (最多19个字符): ";
        // 使用wstring临时存储宽字符输入
        wstring input_wname;
        getline(wcin, input_wname);
        
        // 转换为窄字符串并复制到record.name
        string name = converter.to_bytes(input_wname);
        strncpy(new_record.name, name.c_str(), CHAR_ARRAY_MAX - 1);
        new_record.name[CHAR_ARRAY_MAX - 1] = '\0'; // 确保字符串以null结尾
        
        // 定位到指定位置并写入新的结构体数据
        file.clear(); // 清除任何可能的错误标志
        file.seekp(record_pos, ios::beg);
        
        // 检查文件指针是否正确定位
        if(file.tellp() != record_pos) {
            wcout << L"文件指针定位失败，当前位置: " << file.tellp() << L", 期望位置: " << record_pos << endl;
            file.close();
            return false;
        }
        
        file.write(reinterpret_cast<const char*>(&new_record), sizeof(DataRecord));
        
        // 检查写入是否成功
        if(!file.good()) {
            wcout << L"写入结构体数据失败" << endl;
            file.close();
            return false;
        }
        
        wcout << L"结构体数据已更新" << endl;
    }
    
    file.close();
    file.clear();
    return true;
}

// 左值引用重载版本，转发到右值引用版本
bool file_seek_binary(const std::string& filename) noexcept {
    return file_seek_binary(std::string(filename));
}