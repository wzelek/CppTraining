#include <iostream>

template<int Val>
struct fractional {
    /*
    enum {
        value = Val + 1
    };
    */
    constexpr static int value = Val * fractional<Val - 1>::value;
};


template<>
struct fractional<0> {
    constexpr static int value = 1;
};

template<int Index>
struct Fibonacci {
    constexpr static int value = Fibonacci<Index - 2>::value + Fibonacci<Index - 1>::value;
};

template<>
struct Fibonacci<1> {
    constexpr static int value = 1;
};

template<>
struct Fibonacci<0> {
    constexpr static int value = 0;
};

int main() {
    std::cout << fractional<6>::value << '\n';
    std::cout << Fibonacci<8>::value << '\n';
}
