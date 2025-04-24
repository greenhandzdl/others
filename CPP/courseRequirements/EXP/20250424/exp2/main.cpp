#include<iostream>
class Date{
    private:
        using Num = unsigned int;
        Num year {1970},month {1},day {1};
    public:
        Date(Num y,Num m,Num d):year{y},month{m},day{d}{}
        Date(){}
        void print(){
            std::cout << *this<<std::endl;
        }
        friend std::ostream& operator<<(std::ostream& , const Date &);
};
std::ostream& operator<<(std::ostream& os, const Date& D){
    return os<<D.year<<"-"<<D.month<<"-"<<D.day;
}
int main(){
    Date d1;
    d1.print();
    std::cout<<d1;
}