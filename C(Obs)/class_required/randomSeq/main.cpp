#include "randomSeq.h"
#include <algorithm>//std::sort

const int M = 4;//4个老师去开会

//驱动函数
int main(void){
    Member arr[M] = {
            Member("Liu"),
            Member("Yang"),
            Member("Zhang"),
            Member("Wang")
        };
    
    std::sort(arr,arr+M);

    for(int i=0;i<M;i++){
        std::cout<<"第"<<i+1<<"次，"<<arr[i]<<"老师去开会"<<std::endl;
    }

}

// g++ main.cpp randomSeq.cpp -o randomSeq.out && ./randomSeq.out