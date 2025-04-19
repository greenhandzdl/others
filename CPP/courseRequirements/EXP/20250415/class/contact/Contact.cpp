#include "contact_required.h"
#include <iostream>
#include <iomanip>

namespace contact{
    void Contact::showContact(void) const{
        if(this->contactStorage.size() == 0){
            ContactMethod::uTUIShow(L"No contact");
        }else{
            ContactMethod::tableHeader();
            for(auto& i : this->contactStorage){
                std::wcout << std::setw(WIDTH) << std::left << i.first << L": " << i.second << std::endl;
            }
        }
        ContactMethod::WaitForUserInput();
    }

    bool Contact::addContact(const Str& name,const Infor& info){
        if(this->contactStorage.find(name) != this->contactStorage.end()){
            return false;
        }else{
            this->contactStorage.emplace(std::make_pair(name,info));
            return true;
        }
    }

    bool Contact::addContact(const std::pair<Str,Infor>& put_pait){
        if(this->contactStorage.find(put_pait.first) != this->contactStorage.end()){
            return false;
        }else{
            this->contactStorage.emplace(put_pait);
            return true;
        }
    }

    bool Contact::findContact(const Str& name) const{
        if(this->contactStorage.find(name) != this->contactStorage.end()){
            return true;
        }else{
            return false;
        }
    }
    
    bool Contact::sortContact(const Str& property,DB& results) {
        for(auto& i : this->contactStorage){
            if(property == i.second.property)
                results.emplace(i);
        }
        if(results.empty()) return false;
        return true;
    }

    template<typename Info,
    typename = typename std::enable_if<std::is_same<Info, Infor>::value>::type>
    bool Contact::modContact(const Str& name, Info&& info) {
        auto it = contactStorage.find(name);
        if (it != contactStorage.end()) {
            it->second = std::forward<Info>(info);
            return true;
        }
        return false;
    }

    bool Contact::delContact(const Str& name){
        if(this->contactStorage.find(name) != this->contactStorage.end()){
            this->contactStorage.erase(name);
            return true;
        }else{
            return false;
        }
    }

    bool Contact::isEmptyContact(void){
        if(this->contactStorage.empty()) return true;
        return false;
    }
}