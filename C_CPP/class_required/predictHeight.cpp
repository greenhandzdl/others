/*
设 faHeight 为其父身高，moHeight 为其母身高，身高预测公式为
男性成人时身高=(faHeight + moHeight)×0.54cm
女性成人时身高=(faHeight×0.923 + moHeight)/2cm

此外，如果喜爱体育锻炼，那么可增加身高 2%；如果有良好的卫生饮食习惯，那么可增加 身高 1.5%。
编程从键盘输入用户的性别（用字符型变量 sex 存储，输入字符 F 表示女性，输 入字符 M 表示男性）
父母身高（用实型变量存储，faHeight 为其父身高，moHeight 为其母身高）
是否喜爱体育锻炼（用字符型变量 sports 存储，输入字符 Y 表示喜爱，输入字符 N表示不喜爱）
是否有良好的饮食习惯等条件（用字符型变量 diet 存储，输入字符 Y 表示良 好，输入字符 N 表示不好）
*/
//g++ predictHeight.cpp -o predictHeight.out && ./predictHeight.out
#include<iostream>
#define FARATIO 0.54
#define MORATIO 2
#define SPORTSFAVORATE 0.02
#define DIETFAVORATE 0.015
using namespace std;
int main(void){
    char sex,sports,diet;
    float  faHeight, moHeight;
    unsigned  height;
    cout << "请输入用户的性别（F/M）" << endl;
    // 输入的时候应该自动转为大写
    cin >> sex;
    sex = toupper(sex);
    
    cout << "请输入用户的父母身高（cm）" << endl;
    cin >> faHeight >> moHeight;
    
    cout << "请输入是否喜爱体育锻炼（Y/N）" << endl;
    cin >> sports;
    sports = toupper(sports);
    
    cout << "请输入是否拥有良好的饮食习惯（Y/N）" << endl;
    cin >> diet;
    diet = toupper(diet);

    if(sex == 'M'){
        height = (faHeight + moHeight)* FARATIO;
    }else{
        height = (faHeight*MORATIO + moHeight)/2;
    }
    if(sports == 'Y'){
        height += height*SPORTSFAVORATE;
    }else{
        height += height*DIETFAVORATE;
    }
    if(diet == 'Y'){
        height += height*DIETFAVORATE;
    }else{
        height += height*SPORTSFAVORATE;
    }
    cout << "预测身高为：" << height << "cm" << endl;
    return 0;
}