//g++ forward_add.cpp -o forward_add.out && ./forward_add.out

#ifndef _FORWARD_ADD_H
#define _FORWARD_ADD_H
#define N 20
#define M 3
#endif

#include<iostream>

//记得使用delete []
//有 N 个整数，使前面各数顺序循环后移 m 个位置 ， 编写一个函数实现以上功能，在主函数中输入 n 个整数并输出调整后的 n 个数。
void *forward_add(int *,const int &,int *,const int &);

int main(void){
    int arr[N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int append[M] = {21,22,23};
    int *result = (int *)forward_add(arr,N,append,M);
    for(int i=0;i<N+M;i++)
        std::cout<<result[i]<<" ";
        std::cout<<std::endl;
    delete [] result;
}


void *forward_add(int *source,const int &n,int *append,const int &m){
    int *temp = new int[n+m];
    for(int i=0;i<m+n;i++){
        if(i<m)
            temp[i] = append[i];
        else
            temp[i] = source[i-m];
    }
    return temp;
}