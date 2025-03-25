/*
定义一个车基类Vehicle，含私有成员speed，weight。
派生出自行车类Bicycle，增加high成员；汽车类Car，增加seatNum成员。
从bicycle和car中派生出摩托车类Motocycle。
*/
#include<iostream>
#include<typeinfo>

class Vehicle{
    private:
        using T = int;
        T speed;
        T weight;
    public:
        Vehicle(T speed, T weight):speed(speed),weight(weight){}
        virtual ~Vehicle() = default;
        T getSpeed(){return speed;}
        T getWeight(){return weight;}
        void setSpeed(T speed){this->speed = speed;}
        void setWeight(T weight){this->weight = weight;}
};
class Bicycle:virtual public Vehicle{
    private:
        using T = int;
        T high;
    public:
        Bicycle(T speed, T weight, T high):Vehicle(speed, weight),high(high){}
        virtual ~Bicycle() = default;
        T getHigh(){return high;}
        void setHigh(T high){this->high = high;}
};
class Car:virtual public Vehicle{
    private:
        using T = int;
        T seatNum;
    public:
        Car(T speed, T weight, T seatNum):Vehicle(speed, weight),seatNum(seatNum){}
        virtual ~Car() = default;
        T getSeatNum(){return seatNum;}
        void setSeatNum(T seatNum){this->seatNum = seatNum;}
};
class Motocycle:public Bicycle,public Car{
    private:
        using T = int;
    public:
        Motocycle(T speed, T weight, T high, T seatNum)
        :Vehicle(speed, weight),
        Bicycle(speed, weight, high),Car(speed, weight, seatNum){}
        virtual ~Motocycle() = default;
};

int main(){
    using namespace std;

    Vehicle v(100, 200);
    Motocycle m(100, 200, 300, 400);

    Vehicle *p = &m;
    Motocycle *pm = dynamic_cast<Motocycle*>(p);

    

    cout << v.getSpeed() <<
        typeid(v).name() << endl;

    cout << m.getSpeed() <<
        typeid(m).name() << endl;

    cout << p->getSpeed() <<
        typeid(*p).name() << endl;

    cout << pm->getSpeed() <<
        typeid(*pm).name() << endl;

}