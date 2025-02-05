//定义结构体：名称、价格、库存量
//输入N个商品结构体数组
//找出库存为0的商品
//输出商品

// gcc t3.c -o t3.out && ./t3.out < ./t3.dat

#define N 5
#include<stdio.h>
typedef struct Product{
    char name[50];
    float prices;
    int stock;
}Product;

Product input(void){
    puts("请输入商品名称、价格、库存量:");
    Product UserInput;
    scanf(" %s %f %d",UserInput.name,&(UserInput.prices),&(UserInput.stock));
    return UserInput;
}

int main(void){
    Product Arr[5];
    for(int i = 0;i < N;++i)
        Arr[i] = input();
    
    for(int i = 0;i < N;++i){
        if(!(Arr[i].stock)){
            printf("商品%10s，价格%5.3f,库存量%1d。\n"
                ,Arr[i].name,Arr[i].prices,Arr[i].stock);
        }
    }
}
