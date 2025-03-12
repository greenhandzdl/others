/*
分析和运行下面的程序，注意友元函数dist(point a,point b)的作用。
将友元函数dist(point a,point b)改为Point类的公有成员函数Point ::dist(point &b)，请修改主函数中的相应代码，使程序功能不变。
*/
#include <iostream>
#include <cmath>
using namespace std;
class Point
{
	double x;
	double y;
public:
	Point(double a,double b)
	{
		x=a;
		y=b;
	}
	friend double dist(Point a,Point b);
    double dist(Point &b)
    {
        return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
    }
};
double dist(Point a,Point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void main()
{
	Point p1(1,2);
	Point p2(5,2);
	cout<<dist(p1,p2)<<endl;
}

