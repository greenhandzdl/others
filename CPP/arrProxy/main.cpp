#include <array>
#include <stdexcept>
#include <iostream>

template <typename T, std::size_t N>
class Arr {
public:
    Arr(std::array<T, N>& arr) : data_(arr){}
    T& operator[](std::size_t index) {
        return data_.at(index);
    }
    const T& operator[](std::size_t index) const {
        return data_.at(index);
    }
    std::size_t size() const {
        return data_.size();
    }

private:
    std::array<T, N>& data_; 
};

// Factory function
template <typename T, std::size_t N>
Arr<T, N> make_arr(std::array<T, N>& arr) {
    return Arr<T, N>(arr);
}

int main() {
    std::array<int, 5> my_array = {10, 20, 30, 40, 50};
    Arr<int, 5> arr = make_arr(my_array);

    try {
        std::cout << "arr[2] = " << arr[2] << std::endl; // 输出 30
        std::cout << "arr[10] = " << arr[10] << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Out of range error: " << e.what() << std::endl;
    }

    return 0;
}
