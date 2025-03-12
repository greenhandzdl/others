#include<iostream>

constexpr long long memory_distri = 1E8;
int main(void){
    for(auto i = 0;;++i){
        new char[memory_distri] {'\0'};
        std::cout << i * memory_distri << std::endl;
    }
}