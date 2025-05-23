#include<string>
#include<unordered_map>
#include<utility>
#include<iomanip>
#include<atomic>
#include <thread>
#include <chrono>
#include"contact_configure.h"

#ifndef C_REQ_HIDE
#define C_REQ_HIDE
namespace contact{

    // Forward Declaration
    class Contact;
    static class ContactMethod{
        public:
            // For User
            static void showMenu(void);
            static bool askUserForInputToAddContact(Contact&);

            static Infor makeInfor(void){
                return Infor{
                    .phone = 12345,
                    .wechat = 12345,
                    .address = L"address",
                    .email_address = L"email",
                    .property = L"property",
                };
            };
    
            friend class Contact;
            friend class ContactSync;
        private:
            // For Contact
            static bool saveAsFile(const Contact&,const Str& filename = DEFALULT_FILE_NAME);
            static bool loadFromFile(Contact&,const Str& filename = DEFALULT_FILE_NAME);
            
            static void uTUIShow(const Str& message);
            static void aLineOfForm(const Num);
            static void tableHeader(void);
    
            static void WaitForUserInput(void);
            static decltype(auto) iWaitForUserInput(void);
    
            static void cleanUserInput(void);
    
        }ContactMethod;
    class ContactSync {
        private:
            std::thread syncThread;
            std::atomic<bool> stopFlag{false}; // 添加停止标志作为成员变量
            void autoSave(Contact& contact);
        public:
            ContactSync(Contact& contact);
            ~ContactSync();
        };


    class Contact{
    private:
        DB contactStorage;
        std::atomic<unsigned short int> flags ;
        ContactSync contactSync { *this };
    
    public:
        friend class ContactMethod;
        friend class ContactSync;
    
        enum ContactFlags {
            LOAD_FROM_FILE_FLAG = 1 << 0,
            AUTOSAVE_FLAG = 1 << 1,
            SAVE_WHEN_EXIT_FLAG = 1 << 2,
        };
    
        void setFlag(ContactFlags flag) {
            flags |= flag;
        }    
        void clearFlag(ContactFlags flag) {
            flags &= ~flag;
        }
        bool isFlagSet(ContactFlags flag) const {
            return flags & flag;
        }    
        Contact(unsigned short int _flags = LOAD_FROM_FILE_FLAG);
        ~Contact();

        void showContact(void) const;
        bool addContact(const Str&,const Infor&);
        bool addContact(const std::pair<Str,Infor>&);
        bool findContact(const Str&) const;
        bool sortContact(const Str&,DB&);//根据属性

        template<typename Info,
                typename = typename std::enable_if<
                        std::is_same<Info, Infor>::value
                >::type
            >
        bool modContact(const Str& name, const Info&& info){
            auto it = contactStorage.find(name);
            if (it != contactStorage.end()) {
                it->second = std::forward<Info>(info);
                return true;
            }
            return false;
        }

        bool modContact(const Str& name, Infor info){
            auto it = contactStorage.find(name);
            if (it != contactStorage.end()) {
                it->second = std::move(info);
                return true;
            }
            return false;
        }

        bool delContact(const Str&);//删除找到的第一个
        void cleanContact(void){
            contactStorage.clear();
        };
        bool isEmptyContact(void);
        
        void saveAsFile(void) const{
            ContactMethod::saveAsFile(*this);
        }
        void loadFromFile(void){
            ContactMethod::loadFromFile(*this);
        }
    };

}


#endif
