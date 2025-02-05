#include<stdio.h>

int main(void){
    float i = 0;//可以修改i的类型
    puts("请输入一个float类型数据，接下来会给出相应储存：");
    //puts("请输入一个int类型数据，接下来会给出相应储存：");
    scanf("%f",&i);
    FILE *p;
    if((p = fopen("print_stor.dat","w"))==NULL){
        perror("fopen");
        return -1;
    };
    fwrite(&i,sizeof i,1,p);
    fclose(p);
    return 0;
}
/*
输入:123(int)
输出:01111011 0000...(7B0000)
输入:-123(int)
输出:10000101 1111111111111111(85FFFF)

输入:123.000
输出:                   F6      42
输出:0000000000000000 11110110 01000010
od输出:0000 43f6

输入:-123.000
输出:                   F6      c2
输出:0000000000000000 11110110 11000010
输出:8.852002399139869e-41
输出:1(有符号) + 133(133-128=5) + 118
//大端法 低位存低位，高位存高位
//符号位 + 指数位, 8位 + 尾数位, 23位
疑问:对于float类型变量，为什么不是先储存符号位，而是在较高位（最高的字节里第一位储存）？
可能回复:在mac电脑的字节储存中，编码顺序有些不同。编码数字大的地方反而是低位。但总体而言，在一字节存储中，顺序正常。字节存储中，有些变化。
反驳:vscode hex查看器问题，od输出值符合预期
*/