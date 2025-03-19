#include <iostream>
using namespace std;
class Box{
public:
	Box(int=10,int=10,int=10); 
	Box(Box& b);
	int volume( );
private:
	int height;
	int width;
	int length;
};
Box::Box(Box& b)
{
	height = b.height;
	width = b.width;
	length = b.length;
	cout<<"copy constructor"<<endl;
}

Box::Box(int h,int w,int len)
{
	height=h;
	width=w;
	length=len;
	cout<<"constructor"<<endl;
}

int Box::volume( )
{
	return(height*width*length); 
}

void func1(Box b) 
{
		cout<<b.volume()<<endl;
}

Box func2( ) 
{
	Box b(20,30);
	return b; 
}

int main( )
{
	Box box1(10,20,10);
	Box box2(box1); 
cout<<box1.volume()<<endl; 
	func1(box1); 
	Box box3;
	box3=func2();
	cout<<box3.volume()<<endl; 
	return 0;
}
