/*
1．main 函数带命令行参数的使用
假设程序编译后生成的可执行文件为 mycal.exe. 在命令行提示符下,通过在 windows 开 始菜单执行 cmd 命令，出现：c:\>，键入 mycal + 100 200 运行的结果为 300；键入 mycal * 100 200  运行的结果为 20000  等。
（1）要求生成的计算器能做+、-、*、/  四种运算。 要求定义和调用函数 int max(int a,int b);找出并返回 a,b 中较大的数
（2）做除法运算的时候要求判断除数是否为零。
*/
// *或者\时需要转义！！
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float addd(float num1, float num2);
float sub(float num1, float num2);
float mul(float num1, float num2);
float divid(float num1, float num2);

int main(int argc, char *argv[]){
    if(argc != 4){
        printf("参数个数错误");
        return 0;
    }

    char op = argv[1][0];
    float num1 = atof(argv[2]);
    float num2 = atof(argv[3]);
    
    switch(op){
        case '+':
            printf("%f", addd(num1, num2));
            break;
        case '-':
            printf("%f", sub(num1, num2));
            break;
        case '*':
            printf("%f", mul(num1, num2));
            break;
        case '/':
            printf("%f", divid(num1, num2));
            break;
        default:
            printf("运算符错误");
            break;
    }
    return 0;
}

float addd(float num1, float num2){
    return num1 + num2;
}
float sub(float num1, float num2){
    return num1 - num2;
}
float mul(float num1, float num2){
    return num1 * num2;
}
float divid(float num1, float num2){
    static float offset = 0.0001;
    if(fabs(num2) <= offset){
        printf("除数不能为零");
        return 0;
    }else{
        return num1 / num2;
    }
}

// gcc main1.c -o main1.out && ./main1.out + 100 200