/*
* 改错:判断素数1～n
*/
// gcc t1.c -o t1.out && ./t1.out
// 素数:2,3,5,7……
#include<stdio.h>
#include<math.h>
int main(void){
    int n,count = 0;
    printf("请输入一个正整数n: ");
    scanf("%d",&n);
    for(int i = 2;i <= n; i++){

        //修复逻辑：当n≤3时，内循环会被跳过，从而无法判断。
        switch (i){
        case 2:
            count = 1;
            break;
        default:
            count = 2;
            break;
        }

        //判断i是不是素数
        for(int j = 2;j <= sqrt(i);j++){
            //printf("i=%d,j=%d\n",i,j);
            if((i % j) == 0)
                continue;
            else if(j - sqrt(i) >= -1){//修复逻辑：当即将进行到内循环最后一次时，才判断是否为素数
                //printf("AAA i=%d,j=%d\n",i,j);
                count++;
            }
        }
    }
    printf("1到%d之间素数个数是:%d\n",n,count);
    return 0;
}