#include<iostream>
class Point{
    private:
        int x,y;
    public:
        Point(int a = 0,int b = 0){
            this->x=a;
            this->y=b;
        }
        void move(int xoffset,int yoffset){
            x+=xoffset;
            y+=yoffset;
        }
        int getX(){return x;}
        int getY() {return y;}
};

class Rectangle :protected Point{
    private:
        int length,width;
    public:
        using Point::getX;
        using Point::getY;
        using Point::move;
        Rectangle(int x,int y,int l,int w):Point(x,y){
            length=l;
            width=w;
        }
        int getLength(){return length;}
        int getWidth(){return width;}
};

int main(){
    Rectangle r(0,0,8,4);
    r.move(23,56);
    std::cout<<r.getX()<<", "<<r.getY()<<" ,"<<r.getLength()<<" ,"<<r.getWidth()<<std::endl;
}