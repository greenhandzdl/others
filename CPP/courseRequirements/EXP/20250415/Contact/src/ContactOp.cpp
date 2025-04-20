#include "contact_configure.h"
#include "contact_required.h"
namespace contact{
    std::wistream& operator>>(std::wistream& is, CStr& str) {
        is.getline(str, MAX_CSTR_LEN_USE);
        return is;
    }
    
    std::ostream& operator<<(std::ostream& os, const Infor& inf) {
            return os
                << std::setw(WIDTH) << std::left << inf.phone << " " 
                << std::setw(WIDTH) << std::left << inf.wechat << " "
                << std::setw(WIDTH) << std::left << reinterpret_cast<const char*>(inf.address) << " "
                << std::setw(WIDTH) << std::left << reinterpret_cast<const char*>(inf.email_address)
                << std::setw(WIDTH) << std::left << reinterpret_cast<const char*>(inf.property)
                << std::endl;
    }
    
    std::wostream& operator<<(std::wostream& os, const Infor& inf) {
            return os 
                << std::setw(WIDTH) << std::left <<  std::to_wstring(inf.phone) << L" " 
                << std::setw(WIDTH) << std::left <<  std::to_wstring(inf.wechat) << L" "
                << std::setw(WIDTH) << std::left <<  inf.address << L" "
                << std::setw(WIDTH) << std::left <<  inf.email_address
                << std::setw(WIDTH) << std::left <<  inf.property 
                << std::endl;
    } 
}
