/*
设计一个汽车类Motor，该类具有可载人数、轮胎数、马力数、生产厂家和车主五个数据成员，
根据Motor类派生出Car类、Bus类和Truck类。
其中Bus类除继承基类的数据成员外，还具有表示车厢节数的数据成员Number；
Truck类除继承基类的数据成员之外，还具有表示载重量的数据成员Weight。
每个类都具有成员函数Display，用于输出各类对象的相关信息。
要求设计一个统一的显示相关信息的全局函数ShowInfo在主函数种调用，主函数中不直接调用类里面的Display函数。
*/
#include<string>
#include<iostream>

class Motor{
    protected:
        using Num = int;
        using DNum = double;
        using Str = std::string;
    private:
        Num 可载人数 {0},轮胎数 {0};
        DNum 马力数 {0.0f};
        Str 生产厂家 {"Null"},车主 {"Null"};  
    public:
        Motor() = default;
        Motor(Num _可载人数,Num _轮胎数,DNum _马力数,Str _生产厂家,Str _车主)
        : 可载人数(_可载人数),轮胎数(_轮胎数),马力数(_马力数),生产厂家(_生产厂家),车主(_车主)
        {}
        virtual ~Motor() = default;
        virtual void Display() const {
            std::cout << "可载人数：" << this->可载人数 << std::endl
                    << "轮胎数:" << this->轮胎数 << std::endl
                    << "马力数:" << this->马力数 << std::endl
                    << "生产厂家:" << this->生产厂家 << std::endl
                    << "车主:" << this->车主 << std::endl;
        }
        // Getter和Setter
        decltype(auto) get可载人数() const noexcept { return this->可载人数; }
        void set可载人数(Num _可载人数){this->可载人数 = _可载人数;}

        decltype(auto) get轮胎数() const noexcept { return this->轮胎数; }
        void set轮胎数(DNum _轮胎数){this->轮胎数 = _轮胎数;}

        decltype(auto) get马力数() const noexcept { return this->马力数; }
        void set马力数(DNum _马力数){this->马力数 = _马力数;}

        decltype(auto) get生产厂家() const noexcept{ return this->生产厂家; }
        void set生产厂家(Str 生产厂家) { this->生产厂家 = 生产厂家; }

        decltype(auto) get车主() const noexcept { return this->车主; }
        void set车主(Str _车主){ this->车主 = _车主; }

};
class Car:public Motor{
    private:
        using Motor::Num,Motor::DNum,Motor::Str;
    public:
        Car() = default;
        Car(Num _可载人数,Num _轮胎数,DNum _马力数,Str _生产厂家,Str _车主)
        : Motor(_可载人数,_轮胎数,_马力数,_生产厂家,_车主)
        {}
        void Display() const override{
            Motor::Display();
        }

};
class Bus:public Motor{
    private:
        using Motor::Num,Motor::DNum,Motor::Str;
        Num Number {0};
    public:
        Bus() = default;
        Bus(Num _可载人数,Num _轮胎数,DNum _马力数,Str _生产厂家,Str _车主,Num _Number)
        : Motor(_可载人数,_轮胎数,_马力数,_生产厂家,_车主),Number(_Number)
        {}
        void Display() const override{
            Motor::Display();
            std::cout << "车厢节数:" << this->Number << std::endl;
        }
        // getter&&setter
        decltype(auto) getNumber() const noexcept { return this->Number; }
        void setNumber(Num _Number) { this->Number = _Number; }

};
class Truck:public Motor{
    private:
        using Motor::Num,Motor::DNum,Motor::Str;
        DNum Weight {0};
    public:
        Truck() = default;
        Truck(Num _可载人数,Num _轮胎数,DNum _马力数,Str _生产厂家,Str _车主,DNum _Weight)
        : Motor(_可载人数,_轮胎数,_马力数,_生产厂家,_车主),Weight(_Weight)
        {}
       void Display() const override{
            Motor::Display();
            std::cout << "载重量:" << this->Weight << std::endl;
       }
       // getter && setter
       decltype(auto) getWeight() const noexcept { return this->Weight; }
       void setWeight(DNum _Weight) { this->Weight = _Weight; }
};
void ShowInfo(const Motor& _motor){
    _motor.Display();
}
int main(){
    Motor motor(4,4,100.0,"BMW","Bob");
    Car car(4,4,100.0,"BMW","Bob");
    Bus bus(4,4,100.0,"BMW","Bob",4);
    Truck truck(4,4,100.0,"BMW","Bob",1000.0);

    Motor * (arr[4]) = {&motor,&car,&bus,&truck};

    for(auto i:arr){
        ShowInfo(*i);
        std::cout << std::endl;
    }
    
}