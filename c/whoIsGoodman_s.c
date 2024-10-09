/*
有四位同学中的一位做了好事，不留名，表扬信来了之后，校长问这四位是谁做的好事。
A说：不是我。
B说：是C。
C说：是D。
D说：他胡说。
已知三个人说的是真话，一个人说的是假话。现在要根据这些信息，找出做了好事的人。
*/

#include<stdio.h>
typedef enum{
    甲=1,乙,丙,丁
} PEO;
char defPEO(PEO);
int main(void){
    //实现思路:用int来表示对应状态
    unsigned int status[4];
    status[0]=0b0111,
    status[1]=0b0010,
    status[2]=0b0001,
    status[3]=0b1110;
    char (*f)(PEO);
    f = defPEO;

    unsigned int i =0b1000;
    PEO j=丁;
    for(;j >= 甲;i>>=1,j--){
        if(((status[0]&i) + (status[1]&i) + (status[2]&i) + (status[3]&i) ) >>(j-1)==3){
            (*f)(j);
            break;
        }
    }
    return 0;
}
char defPEO(PEO peo){
    switch (peo)
    {
    case 甲:
        puts("是甲同学做的好事");
        break;
    case 乙:
        puts("是乙同学做的好事");
        break;
    case 丙:
        puts("是丙同学做的好事");
        break;
    case 丁:
        puts("是丁同学做的好事");
        break;
    default:
        perror("发生错误");
        return 'E';
    }
    return 0;
}