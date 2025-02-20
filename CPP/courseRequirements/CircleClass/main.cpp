#include<iostream>
#include<iomanip>

class Circle{
    private:
        typedef double dat;
        const dat PI = 3.14159265358979323846;
        dat radius;
        dat area;
        dat circumference;
    public:
        Circle(dat&& r = 0) : radius(r),area(r*r*PI),circumference(2*r*PI){
            std::cout << "Circle constructor" << std::endl;
        }
        Circle(Circle& c) = default;
        Circle(Circle&& c) = default;
        Circle& operator=(const Circle& other) = default;
        Circle& operator=(Circle&& other) = default;
        virtual ~Circle(){
            std::cout << "Circle destructor" << std::endl;
        }
        void show(){
            using namespace std;
            cout << setprecision(3) << fixed
            << setw(16) << "radius: " << setw(8) <<radius << endl
            << setw(16) << "area: " << setw(8) <<area << endl
            << setw(16) << "circumference: " << setw(8) <<circumference << endl;
        }
        friend std::ostream& operator<<(std::ostream& os, Circle& c){
            using namespace std;
            os << setprecision(3) << fixed
            << setw(16) << "radius: " << setw(8) <<c.radius << endl
            << setw(16) << "area: " << setw(8) <<c.area << endl
            << setw(16) << "circumference: " << setw(8) <<c.circumference << endl;
            return os;
        }
};

int main(void){
    Circle c1 = 5,c2 = c1;
    c1.show();
    c2.show();
}