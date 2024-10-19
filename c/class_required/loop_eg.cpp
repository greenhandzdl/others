//实现从1 到20 之间的偶数累加，奇数相乘，并将偶数累加的结果输出， 奇数相乘的结果输出。
//分别使用while循环、do...while循环、for循环实现。
//g++ loop_eg.cpp -o loop_eg.out && ./loop_eg.out
#include <iostream>
using std::cout;
using std::endl;

int while_loop(const int);
int do_while_loop(const int);
int for_loop(const int);

int main(void){
    int a(0),b(0),c(0);
    a = while_loop(20);
    b = do_while_loop(20);
    c = for_loop(20);
    cout << "while_loop: " << a << endl
        << "do_while_loop: " << b << endl
        << "for_loop: " << c << endl;
    return 0;
}

int while_loop(const int n){
    int i(0),sum(0),multiplies(1);
    while(++i<n){
        if(i%2)
            multiplies *= i;
        else
            sum += i;
    }
    cout << "odd results:" << multiplies << endl
        << "even results:" << sum << endl;
    return multiplies + sum;
}

int do_while_loop(const int n){
    int i(1),sum(0),multiplies(1);
    do{
        if(i%2)
            multiplies *= i;
        else
            sum += i;
    }while(++i<n);
    cout << "odd results:" << multiplies << endl
        << "even results:" << sum << endl;
    return multiplies + sum;
}
int for_loop(const int n){
    int sum(0),multiplies(1);
    for(int i(1);i<n;i++){
        if(i%2)
            multiplies *= i;
        else
            sum += i;
    }
    cout << "odd results:" << multiplies << endl
        << "even results:" << sum << endl;
    return multiplies + sum;
}