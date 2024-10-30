// g++ c_string_cmp_self.cpp -o c_string_cmp_self.out && ./c_string_cmp_self.out

#include<iostream>
using std::cout;
using std::endl;

//编程判断输入的一串字符是否为“回文”。所谓“回文”，是指顺读和倒读都一样的字符串
bool IsReverse(const char *,const char *);
char* findArrEnd(const char *);
bool IsReverse(const char *);

int main(void){
    const char* ptr = "abccba";
    IsReverse(ptr,ptr+5);
    return IsReverse(ptr);
}

bool IsReverse(const char *p_start,const char *p_end){
    for(int i = 0;&p_end[-i] - &p_start[i] > 0;i++){
        /*测试
        cout << i << " "
            << &p_end[-i] - &p_start[i]  << " "
            << p_start[i] << p_end[-i]
            << endl;
        */
        if(p_start[i] != p_end[-i]){
            cout << "False"
                << endl;
            return false;
        }
    }
    cout << "True"
        << endl;
    return true;
}

char* findArrEnd(const char* ptr){
    while(*ptr)
        ptr++;
    return (char*)ptr-1;
}

bool IsReverse(const char* ptr){
    return IsReverse(ptr,findArrEnd(ptr));
}