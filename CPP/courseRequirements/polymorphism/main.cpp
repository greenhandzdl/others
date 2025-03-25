/*
下列Shape类是一个表示形状的类，area( )为求图形面积的函数，total( )则是一个通用的用以求不同形状的图形面积总和的函数。
class Shape 
{
public:
    virtual double area() = 0; // 纯虚函数，派生类必须实现此函数
};

double total(Shape* s[], int n) 
{
    double sum = 0.0; // 初始化总面积为0
    for (int i = 0; i < n; i++) 
    {
        sum += s[i]->area(); // 调用每个对象的area()函数并累加结果
    }
    return sum; // 返回总面积
}
要求：（1）从Shape类派生圆类(Circle)、正方形类（Square），圆类新增数据成员半径（radius），正方形类新增数据成员边长
（a），圆类和正方形类都有构造函数，修改、显示数据成员值的函数，求面积函数。
（2）写出main()函数，计算半径为5.5的圆和边长为9.9的正方形的面积和（必须通过调用total函数计算）。
*/
#include<iostream>

class Shape{
public:
    virtual double area() = 0;
    virtual ~Shape() = default;
protected:
    bool isCalc = false;
    double areas = 0;
};

class Circle : public Shape{
public:
    Circle(double _radius) : radius(_radius) {}
    ~Circle() override = default;
    double area() override {
        if(!Shape::isCalc){
            Shape::areas = PI * radius * radius;
        }
        return Shape::areas;
    }
    void setRadius(double radius) {
        this->radius = radius;
    }
    double getRadius() {
        return radius;
    }
private:
    const static double PI;
    double radius;
};

const double Circle::PI = 3.14;

class Square : public Shape{
public:
    Square(double _side) : side(_side) {}
    ~Square() override = default;
    double area() override {
        if(!Shape::isCalc){
            Shape::areas = side * side;
        }
        return Shape::areas;
    }
    void setSide(double side) {
        this->side = side;
    }
    double getSide() {
        return side;
    }
private:
    double side;
};

double total(Shape* s[], int n) 
{
    double sum = 0.0;
    for (int i = 0; i < n; i++) 
    {
        sum += s[i]->area();
    }
    return sum;
}

int main() {
    Circle circle(5.5);
    Square square(9.9);
    Shape* shapes[2] = {&circle, &square};
    double totalArea = total(shapes, 2);
    std::cout << "Total area: " << totalArea << std::endl;
    return 0;
}