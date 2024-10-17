/*
用 switch 语句编程设计一个简单的计算器程序，要求根据用户从键盘输入的表达式：
操作数 1	运算符 op	操作数 2 
计算表达式的值，指定的算术运算符为加（+）、减（-）、乘（*）、除（/）。 
编程要求：程序能进行浮点数的算术运算，有用户输入输出提示信息。 
提示：因为除法中的除数不能为 0，因此关键在于如何比较浮点变量 data2 和常数 0 是否相等。作为整型变量跟 0 的比较，简单的＝＝就可以解决。
而浮点型等实型变量需要用if (fabs(data2) <= 1e-7)进行判断（即判断其是否足够小）。若使用函数 fabs，需要包含头文件 cmath.h
*/
//g++ calc.cpp -o calc.out && ./calc.out
#include<iostream>
#include<cmath>
const float BIAS (1e-7);

int main(void){
    using namespace std;
    float data1, data2;
    char op;
    cout << "Enter an expression: ";
    cin >> data1 >> op >> data2;
    switch(op){
        case '+':
            cout << data1 << " + " << data2 << " = " << data1 + data2 << endl;
            break;
        case '-':
            cout << data1 << " - " << data2 << " = " << data1 - data2 << endl;
            break;
        case '*':
            cout << data1 << " * " << data2 << " = " << data1 * data2  << endl;
            break;  
        case '/':
            if(fabs(data2) <= BIAS)
                cout << "Divisor can't be zero!" << endl;
            else
                cout << data1 << " / " << data2 << " = " << data1 / data2 << endl;
            break;
        default:
            cout << "Bad operator!" << endl;
    }
    return 0;
}