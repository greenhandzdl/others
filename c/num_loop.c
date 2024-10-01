#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//一个测验程序，用于展示输入数字的逆序，并且求出每一位的和
int main(void){
    unsigned long long int num = 0;
    puts("请输入正数，我将展示每一位的和并且逆序展示他。");
    scanf("%lld",&num);

    unsigned short int dig = 1;
    //一个不太好的算法实现：
    //while(num/((int)pow(10,++dig)));

    //一个测试算法看看能不能解决这个问题
    unsigned long long int div = 10;
    while(num/div)
        div *=10,dig++;

    //不如一个循环同时处理复制等

    printf("有%d位数，对吧？\n",dig);

    unsigned short int *p;
    p=(unsigned short int*)calloc(dig,sizeof(unsigned short int));

    int sum = 0;

    for(int i = 0;i<dig;i++){
        sum+=(p[i]=num%10);
        num/=10;
    }

    printf("这个数字的每一位之和是：%d\n逆序是：",sum);
    for(int i = 0;i<dig;i++){
        printf("%d",p[i]);
    }

    free(p);//忘记清理垃圾了

    return 0;
}