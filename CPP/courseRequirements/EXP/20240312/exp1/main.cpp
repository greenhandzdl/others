/*
设计一个类Cdateinfo，其私有数据成员有year(年)、month(月)、day(日)，要求其满足下述要求。
（1）要求有一个无参数的构造函数，其初始的年、月、日分别为：2000，1，1。
（2）要求有一个带参数的构造函数，起参数分别对应年、月、日。
（3）要求用一个成员函数实现日期的设置。
（4）要求用一个成员函数实现日期的输出。
在上述程序的基础上将（1）和（2）的两个构造函数改为一个带默认参数的构造函数，并使年、月、日的默认值分别为：2000，1，1。
*/
#include <iostream>
class Cdateinfo
{
private:
    using T1 = long;
    using T2 = short int;

    T1 year { 2000 };
    T2 month { 1 } ,
            day { 1 };
public:
    constexpr Cdateinfo() = default;
    constexpr Cdateinfo(const T1 _year,const T2 _month,const T2 _day ) noexcept
    :year(_year),month(_month),day(_day) {}
    constexpr void setDate(const T1 _year,const T2 _month,const T2 _day ) noexcept
    {
        year = _year;
        month = _month;
        day = _day;
    }

    static void printDate(const Cdateinfo &cd) noexcept
    {
        std::cout << cd.year << "/" << cd.month << "/" << cd.day << std::endl;
    }
    /*
    constexpr Cdateinfo(const T1 _year = 2000,const T2 _month = 1,const T2 _day = 1) noexcept
    :year(_year),month(_month),day(_day) 
    {}
    */
};

int main(){
    constexpr auto cd = Cdateinfo(2000,1,1);
    auto cd1 = Cdateinfo(2000,1,1);
    Cdateinfo::printDate(cd1); 
}