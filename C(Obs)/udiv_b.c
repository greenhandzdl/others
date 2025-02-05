#include<stdio.h>

int udiv_b(unsigned int);
//用来打印十进制数转二进制数的值

int main(void){
    return udiv_b(4);
}

int udiv_b(unsigned int num){
    int tmp = num%2;
    num=num>>1;
    (tmp||num)?udiv_b(num):printf("转换值是：\n");
    printf("%d",tmp);
    return 0;
}