/*
将冒泡排序中的用于比较之后的交换部分（即数组a[i]和a[i-1]比较后，若后继元素比前面的元素大，则它们要互换位置）用函数swap(T，T)模板实现。
并写一个主函数分别进行字符数组、整形数组和浮点形数组的数据进行测试。
*/
#include<cstdlib>
#include<algorithm>

#include<iostream>

template<typename T , std::size_t N>
void swap(T (&arr)[N]){
    if(N > 2){
        for(int i = 0; i < N; i++){
            for(int j=i;j < N;j++){
                if(arr[i] < arr[j]){
                    std::swap(arr[i],arr[j]);
                }
            }
        }
    }
}

int main(){
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    // int arr[] = {10,9,8,7,6,5};
    for(auto i : arr){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    swap<int>(arr);
    for(auto i : arr){
        std::cout << i << " ";
    }
}