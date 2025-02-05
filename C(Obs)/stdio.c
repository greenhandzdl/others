#include<stdio.h>
#include<ctype.h>

int stdio(void);
/*
*用于接受用户输入并且打印输入
*在unix一般ctrl d来模拟EOF信号，windows似乎是ctrl z
*可以用重定向来忽略这些问题
*/

int main(void){
    return stdio();
}

int stdio(void){
    int ch = '0';
    /*
    printf("请输入任意字符并且按下回车键，程序会进行复读哦～\n");
    printf("退出某项复读的方式是模拟EOF信号\n");
    printf("正在复读:\n");
    while ((ch=getchar()) != EOF)
        putchar(ch);
    */
    do{
        printf("请输入任意字符并且按下回车键，程序会进行复读哦～\n");
        printf("退出某项复读的方式是模拟EOF信号\n");
        printf("正在复读:\n");
        while ((ch=getchar()) != EOF)
            putchar(ch);
        clearerr(stdin);//清理被程序设置stdin关闭的标志，打开标准输入
        //while(!isspace(ch=getchar()));//似乎没什么关系，因为ctrl d并不会加入什么blank和space
        printf("\n输入q进行退出：\n");
        switch (toupper(ch=getchar())){
            //if处理更好，也可以尝试switch语句不用break中断来连接几个选项
            case 'Q':
                goto quit;
                break;
            default:
                break;
        }
    }while(1);
    quit:return 0;
}