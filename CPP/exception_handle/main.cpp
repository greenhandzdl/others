#include <exception>
#include <iostream>
#include <cstdlib>

class overflowException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Overflow exception";
    }
};
long double divided(long double &a, long double &b) throw(overflowException){
    if(b == 0){
        throw overflowException();
    }
    return a/b;
}

int main(){
    using std::cout;
    using std::endl;
    using std::cin;
    for(;;)
        try{
            long double a, b;
            cout << "Enter two numbers: ";
            cin >> a >> b;
            cout << "Result: " << divided(a, b) << endl;
        }
        catch(overflowException &e){
            cout << e.what() << endl;
            break;
        }
    exit(EXIT_SUCCESS);
}

// g++ -std=c++11 main.cpp -o main.out && ./main.out