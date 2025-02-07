#include <iostream>
#include <iterator>
int main(void){

    /*
    copy(std::istream_iterator<char,char>(std::cin), // 输入流迭代器：要读取数据类型char 输入流使用输入类型char
        std::istream_iterator<char,char>(),
        std::ostream_iterator<char,char>(std::cout," ")); // 输出流迭代器：要输出数据类型char 输出流使用输出类型char
    */

   // 针对 wchar_t 类型的输入输出流迭代器
   // 中文优化
    std::wcin.imbue(std::locale("zh_CN.UTF-8"));
    std::wcout.imbue(std::locale("zh_CN.UTF-8"));
    try{
        std::copy(std::istream_iterator<wchar_t, wchar_t>(std::wcin),
            std::istream_iterator<wchar_t, wchar_t>(),
            std::ostream_iterator<wchar_t, wchar_t>(std::wcout, L" "));
    }catch(std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}

// g++ -std=c++11 main.cpp -o main.out && ./main.out