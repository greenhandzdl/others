#include <iostream>

extern "C" {
    void hello() {
        std::cout << "Hello from dynamic library!" << std::endl;
    }

    int add(int a, int b) {
        return a + b;
    }
}

// g++ -fPIC -shared mylib.cpp -o libmylib.so