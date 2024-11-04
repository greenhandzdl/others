#include<stdio.h>

#define ROWS 3
#define COLS 3

//实现数组内所有元素的加法
int sumA(int [ROWS][COLS]);
int sumB(int [][COLS],int);
int sumC(int rows,int cols,int arr[rows][cols]);

int main(void){ //驱动函数
    return sumC( 3,3,(int [3][3]) {{1,2,3},{4,5,6},{7,8,9}});
}
/*
* 注意；以下传递的都是ptr，sumB更加常见，sumC兼容性不如sumB
*/
int sumA(int arr[ROWS][COLS]){ 
    int tot = 0;
    int r = 0 , c = -1; 
    do{
        c = -1;
        while(++c<COLS){
            tot += arr[r][c];
        }
    }while(++r<ROWS);
    printf("tot=%d",tot);
    return tot;
}
int sumB(int arr[][COLS],int rows){ //指针，等价于int (*arr)[COLS]
    int tot = 0;
    int r = 0 , c = -1; 
    do{
        c = -1;
        while(++c<COLS){
            tot += arr[r][c];
        }
    }while(++r<rows);
    printf("tot=%d",tot);
    return tot;
}
int sumC(int rows,int cols,int arr[rows][cols]){ //VLA
    int tot = 0;
    int r = 0 , c = -1; 
    do{
        c = -1;
        while(++c<cols){
            tot += arr[r][c];
        }
    }while(++r<rows);
    printf("tot=%d",tot);
    return tot;
}