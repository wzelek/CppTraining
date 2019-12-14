#include <iostream>
#include <functional>
#include <vector>

struct Operation {
    Operation(int val)
        : val{val} {}
    int operator()(int v) {
        return val * v * 12;
    }
private:
    int val;
};


int foo(int v) {
    return v * 12;
}

int main() {
    Operation operation{1};
    int a = 1;
    auto op1 = [ma = a](int v) mutable -> int { ma++; return ma * v * 12; };
    std::function<int(int)> op2 = [a](int v) mutable { a++; return a * v * 12; };
    op2 = op1;
    op2 = foo;
    std::vector<std::function<int(int)>> myFunctions = {[](int v) { return v * 33; }, foo, operation};

    static std::function<int(int)> myLambda = [](int val) -> int {
        if (val == 0) {
            return 1;
        }
        return myLambda(--val);
    };
    myLambda(5);

    std::cout << op1(12) << '\n';
}
