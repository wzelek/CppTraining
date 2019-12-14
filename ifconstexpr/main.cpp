#include <iostream>
#include <vector>

template<int I>
auto foo() {
    if constexpr (I % 2) {
        return 1545.0;
    } else {
        return 1232;
    }
}

int main() {
    std::cout << foo<1>() << '\n';

    auto myLambda = [](auto a, auto b) {
        return a + b;
    };
    std::cout << myLambda(12.3, 44UL) << '\n';
    std::vector vec = {1, 2, 3, 4, 50};
}
