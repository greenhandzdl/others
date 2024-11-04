#include "randomSeq.h"

Member::Member(const std::string& name): memberName(name){
    static bool isSeeded = false;
    if(!isSeeded){
        //获取当前时间并设置srand()参数
        time_t currentTime;
        time(&currentTime);
        srand(static_cast<unsigned int>(currentTime));
        isSeeded = true;
    }

    id = rand();

    std::cout << "Member " << memberName << " created with id " << id << std::endl;
}
bool Member::operator<(const Member& para) const{
    return (id < para.id) ? true : false;
}
bool Member::operator>(const Member& para) const{
    return (id > para.id) ? false : true;
}
bool Member::operator==(const Member& para) const{
    return (id == para.id) ? true : false;
}
bool Member::operator!=(const Member& para) const{
    return (id != para.id) ? true : false;
}
std::ostream& operator<<(std::ostream& os, const Member& para){
    os << para.memberName;
    return os;
}