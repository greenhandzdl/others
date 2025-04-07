#include "file_op.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <locale>
#include <codecvt>

bool menu(MenuOptions& choice) noexcept {
    using namespace std;

    // 设置本地化支持中文
    setlocale(LC_ALL, "zh_CN.UTF-8");
    locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
    wcin.imbue(utf8_locale);
    wcout.imbue(utf8_locale);
    wcerr.imbue(utf8_locale);
    wclog.imbue(utf8_locale);

    wcin.exceptions(std::ios::failbit);

    wcout << internal
        << setw(20) 
        << "文件操作菜单" << endl
        << left
        << setfill(L'=')
        << setw(40) << L"==========" << endl
        << setfill(L' ')
        << setw(20) << L"1. 退出程序" 
        << setw(20) << L"2. 创建文件" << endl
        << setw(20) << L"3. 读取文件" 
        << setw(20) << L"4. 写入文件" << endl
        << setw(20) << L"5. 创建二进制文件" 
        << setw(20) << L"6. 读取二进制结构体" << endl
        << setw(20) << L"7. 写入二进制结构体" 
        << setw(20) << L"8. 定位二进制结构体" << endl
        << setfill(L'-')
        << setw(40) << L"-" << endl
        << setfill(L' ')
        << L"请输入选项 (1-8): "
        << setfill(L' ') << right;

    int userInput;
    try {
        wcin >> userInput;
        if(userInput < 1 || userInput > 8) {
            std::wclog << L"输入错误，返回" << endl;
            return false;
        } 
        choice = static_cast<MenuOptions>(userInput);
        return true;
    } catch(std::ios::failure& e) {
        std::wcerr << e.what() << std::endl;
        std::wclog << L"检测输入不是int类型" << std::endl;
        throw;
    }
    return false;
}

bool filename_get(std::string& filename) noexcept {
    using namespace std;
    wstring wfilename;
    wcout << L"请输入文件名：";
    if(wcin >> wfilename) {
        // 将宽字符串转换为窄字符串
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        filename = converter.to_bytes(wfilename);
        return true;
    }
    return false;
}

// 使用右值引用和完美转发的版本
bool file_make(std::string&& filename) noexcept {
    using namespace std;
    ofstream file(filename.c_str(), ios_base::out|ios_base::trunc);
    if(!file.is_open()) {
        wcerr << L"文件打开失败" << endl;
        return false;
    }
    file << "" << flush;
    file.close();
    file.clear();
    return true;
}

// 左值引用重载版本，转发到右值引用版本
bool file_make(const std::string& filename) noexcept {
    return file_make(std::string(filename));
}

// 使用右值引用和完美转发的版本
bool file_read(std::string&& filename) noexcept {
    using namespace std;
    ifstream file(filename.c_str(), ios_base::in);
    if(!file.is_open()) {
        wcerr << L"文件打开失败" << endl;
        return false;
    }
    // 使用wstring存储文件内容
    string content;
    copy(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), back_inserter(content));
    
    // 转换为宽字符串并输出
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    wcout << converter.from_bytes(content);
    file.close();
    file.clear();
    return true;
}

// 左值引用重载版本，转发到右值引用版本
bool file_read(const std::string& filename) noexcept {
    return file_read(std::string(filename));
}

// 使用右值引用和完美转发的版本
bool file_write(std::string&& filename) noexcept {
    using namespace std;
    ofstream file(filename.c_str(), ios_base::out|ios_base::app);
    if(!file.is_open()) {
        wcerr << L"文件打开失败" << endl;
        return false;
    }
    // 提示用户输入内容
    wcout << L"请输入要写入的内容: ";
    wcout.flush(); // 确保提示立即显示
    
    // 确保输入缓冲区是干净的
    if(wcin.peek() == L'\n') {
        wcin.ignore();
    }
    
    // 读取宽字符输入
    wstring content;
    getline(wcin, content);
    
    // 转换为窄字符串
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    string utf8_content = converter.to_bytes(content);
    
    // 使用STL算法copy和迭代器写入文件
    copy(utf8_content.begin(), utf8_content.end(), ostreambuf_iterator<char>(file));
    
    wcout << L"内容已写入文件" << endl; // 添加反馈信息

    file.flush();
    file.close();
    file.clear();
    return true;
}

// 左值引用重载版本，转发到右值引用版本
bool file_write(const std::string& filename) noexcept {
    return file_write(std::string(filename));
}