#include<cctype>
#include<string>
#include<unordered_map>
#include<iostream>
#include<iomanip>
#ifndef CONTACT_CONFIGURE_H
#define CONTACT_CONFIGURE_H

namespace contact{
    using Str = std::wstring;
    constexpr size_t MAX_CSTR_LEN = 32;
    constexpr size_t MAX_CSTR_LEN_USE = MAX_CSTR_LEN - 1;
    using CStr = wchar_t[MAX_CSTR_LEN]; 
    using Num = unsigned long long;
    using Infor = struct Informantion{
        Num phone;
        Num wechat;
        CStr address;
        CStr email_address;
        CStr property;
    };
    constexpr int WIDTH = 15;
    constexpr int WLENGTH = WIDTH * 6;
    using DB = std::unordered_map<Str,Infor>;
    constexpr CStr DEFALULT_FILE_NAME = L"backup.db";

    std::wistream& operator>>(std::wistream& is, CStr& str);

    //考虑到存储方便,保存会采用截断
    //对兼容性可能没有保证

    constexpr char MenuText[] = R"(
        Contact Management System
        =========================
        1. Show Contacts
        2. Add Contact
        3. Find Contact
        4. Modify Contact
        5. Delete Contact
        6. Check if Empty
        7. Save to File
        8. Load from File
        9. Exit
        =========================
        Please enter your choice: )";

        std::ostream& operator<<(std::ostream& os, const Infor& inf);
    
        std::wostream& operator<<(std::wostream& os, const Infor& inf);
}
#endif