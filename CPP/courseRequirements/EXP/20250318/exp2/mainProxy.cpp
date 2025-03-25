#include <iostream>

// 前向声明
template<typename T>
class Complex;

// 表达式基类（接口）
template<typename Derived>
class ComplexExpr {
public:
    auto real() const { return static_cast<const Derived*>(this)->real(); }
    auto imag() const { return static_cast<const Derived*>(this)->imag(); }
};

// 自定义结果结构体
template<typename T>
struct Result {
    T real_part;
    T imag_part;
};

// 操作类型定义
struct AddOp {
    template<typename T>
    static Result<T> compute(T a_re, T a_im, T b_re, T b_im) {
        return {a_re + b_re, a_im + b_im};
    }
};

struct SubOp {
    template<typename T>
    static Result<T> compute(T a_re, T a_im, T b_re, T b_im) {
        return {a_re - b_re, a_im - b_im};
    }
};

struct MulOp {
    template<typename T>
    static Result<T> compute(T a_re, T a_im, T b_re, T b_im) {
        return {
            a_re * b_re - a_im * b_im,  // 实部
            a_re * b_im + a_im * b_re   // 虚部
        };
    }
};

// 通用操作代理类
template<typename E1, typename E2, typename Op>
class ComplexOP : public ComplexExpr<ComplexOP<E1, E2, Op>> {
    const E1& lhs;
    const E2& rhs;
public:
    ComplexOP(const E1& a, const E2& b) : lhs(a), rhs(b) {}

    auto real() const { 
        return Op::compute(
            lhs.real(), lhs.imag(), 
            rhs.real(), rhs.imag()
        ).real_part; 
    }

    auto imag() const { 
        return Op::compute(
            lhs.real(), lhs.imag(), 
            rhs.real(), rhs.imag()
        ).imag_part; 
    }
};

// 复数类
template<typename T>
class Complex : public ComplexExpr<Complex<T>> {
    T re, im;
public:
    Complex(T r = 0, T i = 0) : re(r), im(i) {}

    // 从代理类构造
    template<typename Expr>
    Complex(const ComplexExpr<Expr>& expr)
        : re(expr.real()), im(expr.imag()) {}

    // 赋值运算符
    template<typename Expr>
    Complex& operator=(const ComplexExpr<Expr>& expr) {
        re = expr.real();
        im = expr.imag();
        return *this;
    }

    // 基础操作
    T real() const { return re; }
    T imag() const { return im; }
};

// 运算符重载
template<typename E1, typename E2>
ComplexOP<E1, E2, AddOp> operator+(
    const ComplexExpr<E1>& a, 
    const ComplexExpr<E2>& b
) {
    return ComplexOP<E1, E2, AddOp>(
        static_cast<const E1&>(a), 
        static_cast<const E2&>(b)
    );
}

template<typename E1, typename E2>
ComplexOP<E1, E2, SubOp> operator-(
    const ComplexExpr<E1>& a, 
    const ComplexExpr<E2>& b
) {
    return ComplexOP<E1, E2, SubOp>(
        static_cast<const E1&>(a), 
        static_cast<const E2&>(b)
    );
}

template<typename E1, typename E2>
ComplexOP<E1, E2, MulOp> operator*(
    const ComplexExpr<E1>& a, 
    const ComplexExpr<E2>& b
) {
    return ComplexOP<E1, E2, MulOp>(
        static_cast<const E1&>(a), 
        static_cast<const E2&>(b)
    );
}

int main() {
    Complex<double> a(1.0, 2.0);
    Complex<double> b(3.0, 4.0);
    Complex<double> c(5.0, 6.0);

    Complex<double> result = (a + b) * c;

    std::cout << "Real: " << result.real() 
              << ", Imag: " << result.imag() << std::endl;
              // 输出 Real: -16, Imag: 54
}