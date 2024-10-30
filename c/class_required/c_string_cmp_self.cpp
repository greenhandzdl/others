//编程判断输入的一串字符是否为“回文”。所谓“回文”，是指顺读和倒读都一样的字符串
#include<iostream>
using std::cout;

int IsReverse(char *,char *);

int IsReverse(char *p_start,char *p_end){
    for(int i = 0;p_end - p_start <= 0;i++)
        if(p_start[i] != p_end[-i]){
            cout << "False";
            return 0;
        }
    cout << "True";
    return 0;
}