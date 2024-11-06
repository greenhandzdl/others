#include<iostream>
#include "linkedList.h"
using linked_list::linkedList;

int main(void){
    using std::cout;
    using std::endl;

    linkedList list('A');
    for(wchar_t temp ('B'); temp <= 'Z'; temp++){
        list.insert(temp);
    }
    for(wchar_t temp ('a'); temp <= 'z'; temp++){
        list.insert(temp);
    }

    cout << "List: " << list << endl;
}

// g++ main.cpp linkedList.cpp -o linkedList.out && ./linkedList.out