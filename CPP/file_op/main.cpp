#include "file_op.h"
#include <iostream>
#include <cstdlib>
#include <locale>
#include <codecvt>

int main(void) {
    // 设置本地化支持中文
    std::setlocale(LC_ALL, "zh_CN.UTF-8");
    std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
    std::wcin.imbue(utf8_locale);
    std::wcout.imbue(utf8_locale);
    std::wcerr.imbue(utf8_locale);
    std::wclog.imbue(utf8_locale);
    
    MenuOptions choice;

    std::string filename;
    std::wcout << L"欢迎使用文件操作程序" << std::endl;

    try {
        while(!menu(choice));
        filename_get(filename);
    } catch(std::ios::failure& e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    switch (choice) {
        case MenuOptions::MAKE_FILE:
            std::wcout << L"创建文件" << std::endl;
            file_make(filename);
            break;
        case MenuOptions::READ_FILE:
            std::wcout << L"读取文件" << std::endl;
            file_read(filename);
            break;
        case MenuOptions::WRITE_FILE:
            std::wcout << L"写入文件" << std::endl;
            std::wcout << L"Unix使用Ctrl+D结束输入，Windows使用Ctrl+Z结束输入" << std::endl;
            file_write(filename);
            break;
        case MenuOptions::MAKE_BINARY_FILE:
            std::wcout << L"创建二进制文件" << std::endl;
            file_make_binary(filename);
            break;
        case MenuOptions::READ_BINARY_FILE:
            std::wcout << L"读取二进制文件" << std::endl;
            file_read_binary(filename);
            break;
        case MenuOptions::WRITE_BINARY_FILE:
            std::wcout << L"写入二进制文件" << std::endl;
            file_write_binary(filename);
            break;
        case MenuOptions::SEEK_BINARY_FILE:
            std::wcout << L"二进制文件随机访问" << std::endl;
            file_seek_binary(filename);
            break;
        case MenuOptions::EXIT:
        default:
            std::cout << "退出程序" << std::endl;
            exit(EXIT_SUCCESS);
            break;
    }

    return 0;
}