#include"contact_required.h"
#include<iostream>
#include<fstream>
#include<cctype>
#include<algorithm>
namespace contact{

    void ContactMethod::showMenu(void){
        std::wcout << std::endl
            << MenuText
            << std::endl;
    }

    bool ContactMethod::askUserForInputToAddContact(Contact& contact){
        std::wstring temp;
        Infor info;
        bool flag = false;
        std::wcout << std::endl
            << L"[M]Notice!The number of character you input is limited to "
            << MAX_CSTR_LEN_USE
            << L" characters.And if you exceed the limit,the input will be truncated."
            << std::endl;
        while(!std::wcin.eof()){
            std::wcout << std::endl
                << L"[M]Please input a name: "
                << std::endl;
            if(! (std::wcin >> temp) )
                break;

            std::wcout << std::endl
                << L"[M]Please input a phone number: "
                << std::endl;
            if(! (std::wcin >> info.phone))
                break;
            
            std::wcout << std::endl
                << L"[M]Please input a wechat: "
                << std::endl;
            if (! (std::wcin >> info.wechat) )
                break;

            std::wcout << std::endl
                << L"[M]Please input a address: "
                << std::endl;
            if(! (std::wcin >> info.address) )
                break;
            
            std::wcout << std::endl
                << L"[M]Please input a email: "
                << std::endl;
            if(! (std::wcin >> info.email_address) )
                break;

            std::wcout << std::endl
                << L"[M]Please input a property: "
                << std::endl;
            if(! (std::wcin >> info.property) )
                break;
            
            contact.addContact(temp,info);
            
            flag = true;

            std::wcout << std::endl
                << L"[M]Add another contact?(Y/N)"
                << std::endl;
            
            if(! (std::wcin >> temp))
                break;
            
            std::transform(temp.begin(),temp.end(),temp.begin(),::tolower);
            if(temp != L"y")
                break;
        }
        ContactMethod::cleanUserInput();
        ContactMethod::WaitForUserInput();
        return flag;
    }

    bool ContactMethod::saveAsFile(const Contact& contact,const Str& filename = DEFALULT_FILE_NAME){
        // binary and append
        std::ofstream file(reinterpret_cast<const char *> (filename.c_str())
                            , std::ios::binary | std::ios::out |std::ios::app);
        if(!file.is_open()){
            std::wcerr << L"File open failed" << std::endl;
            return false;
        }
        for(auto i : contact.contactStorage){
            try{
                file.write(reinterpret_cast<const char*>(&i.first),sizeof(i.first));
                file.write(reinterpret_cast<const char*>(&i.second),sizeof(i.second));
            }catch(std::exception& e){
                std::wcerr << L"File write failed" << std::endl;
                return false;
            }
            
        }
        file.close();
        return true;
    }

    bool ContactMethod::loadFromFile(Contact& contact,const Str& filename = DEFALULT_FILE_NAME){
        Str name;
        Infor info;
        std::ifstream file(reinterpret_cast<const char *> ( filename.c_str() ), // may be a bug
                            std::ios::binary|std::ios::in);
        if(!file.is_open()){
            std::wcerr << L"File open failed" << std::endl;
            return false;
        }
        while(!file.eof()){
            try{
                file.read(reinterpret_cast<char*>(&name),sizeof(name));
                file.read(reinterpret_cast<char*>(&info),sizeof(info));
                contact.contactStorage.emplace(std::make_pair(name,info));
            }catch(std::exception& e){
                std::wcerr << L"File read failed" << std::endl;
                return false;
            }
        }
        file.close();
        return true;
    }

    void ContactMethod::uTUIShow(const Str& message){
        std::wcout << std::endl
            << "Progress: "
            << message
            << std::endl;
    }
    void ContactMethod::aLineOfForm(Num count){
        while(count -- < 1){
            fputs("*",stdout);
        }
    }

    void ContactMethod::tableHeader(void){
        ContactMethod::aLineOfForm(WLENGTH);
        std::wcout << std::endl
            << "|"
            << std::setw(WLENGTH) << L"Name"
            << "|"
            << std::setw(WLENGTH) << L"Phone"
            << "|"
            << std::setw(WLENGTH) << L"Wechat"
            << "|"
            << std::setw(WLENGTH) << L"Address"
            << "|"
            << std::setw(WLENGTH) << L"Email"
            << "|"
            << std::setw(WLENGTH) << L"Property"
            << "|"
            << std::endl;
        ContactMethod::aLineOfForm(WLENGTH);
    }

    void ContactMethod::WaitForUserInput(void) {
        std::wcout << std::endl
                   << L"Press any key to continue..."
                   << std::endl;
    
        if (!std::wcin.get()) {
            std::wcerr << L"Input failed. Exiting..." << std::endl;
        }
    }
    decltype(auto) ContactMethod::iWaitForUserInput(void){
        int returnValue;
        std::wcout << std::endl
                   << L"Please input a number: "
                   << std::endl;
        while(!(std::wcin >> returnValue)){
            std::wcerr << L"Input failed. Please input a number: " << std::endl;
            ContactMethod::cleanUserInput();
        }
        return returnValue;
    }

    void ContactMethod::cleanUserInput(void){
        std::wcin.clear();
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

}
