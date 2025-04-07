#include "file_op.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <locale>
#include <codecvt>
#include <cstring>

// 设置本地化支持中文的函数
void set_struct_utf8_locale() noexcept {
    using namespace std;
    setlocale(LC_ALL, "zh_CN.UTF-8");
    locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
    wcin.imbue(utf8_locale);
    wcout.imbue(utf8_locale);
    wcerr.imbue(utf8_locale);
    wclog.imbue(utf8_locale);
}

// 使用右值引用和完美转发的版本
bool file_write_struct_binary(std::string&& filename) noexcept {
    using namespace std;
    set_struct_utf8_locale(); // 设置UTF-8编码环境
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
bool file_write_struct_binary(const std::string& filename) noexcept {
    return file_write_struct_binary(std::string(filename));
}

// 使用右值引用和完美转发的版本
bool file_read_struct_binary(std::string&& filename) noexcept {
    using namespace std;
    set_struct_utf8_locale(); // 设置UTF-8编码环境
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
bool file_read_struct_binary(const std::string& filename) noexcept {
    return file_read_struct_binary(std::string(filename));
}