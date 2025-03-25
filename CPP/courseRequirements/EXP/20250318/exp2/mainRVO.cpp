#include <iostream>

class Complex {
        private:
        double real;
        double imag;
    public:
        Complex(double r, double i) : real(r), imag(i) {} 

        explicit Complex(double r) : real(r), imag(0) {}// 实数转换

        Complex& operator+=(const Complex &c){
                        real += c.real;
                        imag += c.imag;
                        return *this; // 返回当前对象的引用
                    }
        Complex operator+(Complex c){
            return c += *this;
        }

        Complex& operator-=(const Complex &c){
            this->real -= c.real;
            this->imag -= c.imag;
            return *this;
        }

        Complex operator-(Complex c){
            return c -= *this;
        }

        Complex& operator*=(const Complex &c){
            this->real = this->real * c.real - this->imag * c.imag;
            this->imag = this->real * c.imag + this->imag * c.real;
            return *this;
        }

        Complex operator*(Complex c){
            return c *= *this;
        }

        Complex& operator/=(const Complex &c){
            this->real = (this->real * c.real + this->imag * c.imag) / (c.real * c.real + c.imag * c.imag);
            this->imag = (this->imag * c.real - this->real * c.imag) / (c.real * c.real + c.imag * c.imag);
            return *this;
        }

        Complex operator/(Complex c){
            return c /= *this;
        }

        bool operator==(const Complex &c) const{
            return this->real == c.real && this->imag == c.imag;
        }

        bool operator!=(const Complex &c) const{
            return *this != c;
        }

        bool operator<(const Complex &c) const{
            return this->real < c.real && this->imag < c.imag;
        }

        bool operator>(const Complex &c) const{
           return c < *this;
        }

        bool operator<=(const Complex &c) const{
            return *this < c || *this == c;
        }

        bool operator>=(const Complex &c) const{
            return *this > c || *this == c;
        }

        friend std::ostream& operator<<(std::ostream &os, const Complex &c){
            os << c.real << " + " << c.imag << "i";
            return os;
        }

        friend std::istream& operator>>(std::istream &is, Complex &c){
            is >> c.real >> c.imag;
            return is;
        }

};

int main(void){
    std::cout << "Please input two complex number:" << std::endl;
    Complex c1(0), c2(0);
    std::cin >> c1 >> c2;
    std::cout << "c1 + c2 = " << c1 + c2 << std::endl;
    std::cout << "c1 - c2 = " << c1 - c2 << std::endl;
    std::cout << "c1 * c2 = " << c1 * c2 << std::endl;
    std::cout << "c1 / c2 = " << c1 / c2 << std::endl;
    std::cout << "c1 == c2 = " << (c1 == c2) << std::endl;
    std::cout << "c1 != c2 = " << (c1 != c2) << std::endl;
    // c1 + c2;
}