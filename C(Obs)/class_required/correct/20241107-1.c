#include <stdio.h>

// 全局变量，用于存放函数结果
float real, imag;

// 函数声明
void complex_product(float x1, float y1, float x2, float y2);

int main() {
    float real1, real2, imag1, imag2;
    printf("input 1st complex num:\n");
    scanf("%f %f", &real1, &imag1);
    printf("input 2nd complex num:\n");
    scanf("%f %f", &real2, &imag2);
    complex_product(real1, imag1, real2, imag2);
    printf("product is %f + %fi\n", real, imag);
    return 0;
}

// 函数定义
void complex_product(float x1, float y1, float x2, float y2) {
    real = x1 * x2 - y1 * y2;
    imag = x1 * y2 + x2 * y1;
}

// gcc 20241107-1.c -o 20241107-1.out && ./20241107-1.out