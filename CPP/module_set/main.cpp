// main.cpp
// 你应该先对库进行链接
// g++ -std=c++20 -fmodules-ts -xc++-system-header iostream
import <iostream>;  // 导入模块

int main() {
    using namespace std;
    string message = "Hello, C++20 Modules!";
    cout << message << endl;  // 使用模块中导出的符号
    return 0;
}