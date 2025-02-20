#include<iostream>
#include<iomanip>
namespace CircleNamespace{
    typedef long double dat;
    dat operator""_m(dat value){
        return static_cast<dat>(value * 1);
    }
    dat operator""_dm(dat value){
        return static_cast<dat>(value * 1E-1);
    }

    dat operator""_cm(dat value){
        return static_cast<dat>(value * 1E-2);
    }
    dat operator""_mm(dat value){
        return static_cast<dat>(value * 1E-3);
    }
    
    class Circle{
        private:
            constexpr static dat PI = 3.14159265358979323846;
            static unsigned int count;
            dat radius;
            dat area;
            dat circumference;
        public:
            Circle(dat&& r = 0) : radius(r),area(r*r*PI),circumference(2*r*PI){
                count++;
                std::cout << "#" << count << "Circle constructor" << std::endl;
            }
            operator dat(){
                return this->radius;
            }
            Circle(Circle& c) = delete;
            Circle(Circle&& c) = default;
            Circle& operator=(const Circle& other) = delete;
            Circle& operator=(Circle&& other) = default;
            virtual ~Circle(){
                count--;
                std::cout << "#" << count << "Circle destructor" << std::endl;
            }
            void show(){
                using namespace std;
                cout << setprecision(3) << fixed
                << setw(16) << "#" << count << "Circle" << endl
                << setw(16) << "radius: " << setw(8) <<radius << endl
                << setw(16) << "area: " << setw(8) <<area << endl
                << setw(16) << "circumference: " << setw(8) <<circumference << endl;
            }
            friend std::ostream& operator<<(std::ostream& os, Circle& c){
                using namespace std;
                os << setprecision(3) << fixed
                << setw(16) << "#" << count << "Circle" << endl
                << setw(16) << "radius: " << setw(8) <<c.radius << endl
                << setw(16) << "area: " << setw(8) <<c.area << endl
                << setw(16) << "circumference: " << setw(8) <<c.circumference << endl;
                return os;
            }   
    };
    unsigned int Circle::count = 0;
}
int main(void){
    using namespace CircleNamespace;
    Circle c1 = 5.0_cm,c2 = c1 + 5.0_m;
    c1.show();
    c2.show();
}