#include<stdio.h>
//猜数字游戏，大概框架，如果可能再完善吧。

int numGet(int *guess);//获取一个数值并且检测是否符合输入
int numInitial(int *s,int *g);//获取用户输入，生成随机数
int numJudge(int random,int guess,int *s,int *g);//检测数值是否相等并且打印相关提示符

int main(void){
    int s=0,g =0;
    int status = 0,guess = 0,tried = 0;
    int rand =numInitial(&s,&g);
    for(int i = 0;numJudge(rand,status = numGet(&guess),int *s,int *g),tried++);
    printf("恭喜你成功了，你进行了%d次猜测，终于猜对了是%d的值。",tried,rand);
    return 0;
}