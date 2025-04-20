#include "contact_required.h"
#include <iostream>

using namespace contact;

//驱动函数
int main(void){
    // Contact contact(Contact::AUTOSAVE_FLAG|Contact::SAVE_WHEN_EXIT_FLAG);
    Contact contact(Contact::LOAD_FROM_FILE_FLAG);
    ContactMethod::showMenu();
    int choice = 0;
    std::wstring temp;
    while(true){
        std::cout << "请输入您的选择：";
        if (!(std::cin >> choice)) { // 检查输入是否有效
            std::cin.clear(); // 清除错误标志
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略无效输入
            std::cout << "输入无效，请重新输入。\n";
            continue;
        }

        switch (choice) {
            case 1:
                contact.showContact();
                break;
            case 2:
                ContactMethod::askUserForInputToAddContact(contact);
                break;
            case 3:
                std::cout << "请输入您要查找的联系人姓名：";
                std::wcin >> temp;
                contact.findContact(temp);
                break;
            case 4:
                std::wcout << "请输入您要修改的联系人姓名：";
                std::wcin >> temp;
                contact.modContact(temp,std::move(  ContactMethod::makeInfor() ));
                break;
            case 5:
                std::wcout << "请输入您要删除的联系人姓名：";
                std::wcin >> temp;
                contact.delContact(temp);
                break;
            case 6:
                if (contact.isEmptyContact()) {
                    std::cout << "通讯录为空！" << std::endl;
                } else {
                    std::cout << "通讯录不为空。" << std::endl;
                }
                break;
            case 7:
                contact.saveAsFile();
                break;
            case 8:
                contact.loadFromFile();
                break;
            case 9:
            case 0:
                return 0;
                break;
            default:
                std::cout << "无效选项，请重新输入。\n";
                break;
        }
    }
}