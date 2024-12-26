//计算1～n所有奇数的和
// gcc t2.c -o t2.out && ./t2.out
#include<stdio.h>

int main(void){
    fputs("请输入要计算的1～n所有奇数的和，n: ",stdout);
    int n=0,sum=0;
    scanf("%d",&n);

    for(int i=1;i<=n;++i){
        if(i%2)
            sum += i;
    }
    printf("sum=%d",sum);
    return 0;
}