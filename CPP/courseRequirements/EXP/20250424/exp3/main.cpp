#include <iostream>
class Shape{
    protected:
        using Num = double;
    public:
        virtual Num GetArea() = 0;
        virtual Num GetPerim() = 0;
        virtual ~Shape(){};
};

class Rectangle : public Shape{
    private:
        Num width, height;
    public:
        Rectangle(Num w, Num h) : width(w), height(h){}
        Num GetArea() override{
            return width * height;
        }
        Num GetPerim() override{
            return 2 * (width + height);
        }
};
class Circle : public Shape{
    private:
        Num radius;
        constexpr static Num PI = 3.14;

    public:
        Circle(Num r) : radius(r){}
        Num GetArea() override{
            return PI * radius * radius;
        }
        Num GetPerim() override{
            return 2 * PI * radius;
        }
};
int main(){
    Shape * (shapes[2]);
    shapes[0] = new Rectangle(2, 3);
    shapes[1] = new Circle(2);
    for(int i = 0; i < 2; i++){
        std::cout << shapes[i]->GetArea() << std::endl;
        std::cout << shapes[i]->GetPerim() << std::endl;
    }
    for(int i = 0; i < 2; i++){
        delete shapes[i];
    }
}