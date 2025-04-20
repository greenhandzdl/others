#include "contact_required.h"
#include <iostream>

using namespace contact;

//驱动函数
int main(void){
    Contact contact(Contact::AUTOSAVE_FLAG);
    ContactMethod::showMenu();
    int choice = 0;
    while(true){
        std::cout << "请输入您的选择：";
        std::wcin >> choice;
        if(choice == 0)
            break;
        else if(choice == 1)
            ;
            // contact.addContact();
        else if(choice == 2)
            ;
            // contact.delContact();
        else if(choice == 3)
            ;
            // contact.modContact();
        else if(choice == 4)
            ;
            // contact.findContact();
        else if(choice ==5)
            ;
            // contact.showContact();
        else if(std::wcin.fail()){
            std::cout << "输入错误，请重新输入！" << std::endl;
            std::wcin.clear();
            std::wcin.ignore(INT_MAX,'\n');
            continue;
        }
    }
}