#include <iostream>

template<typename... Args>
void foo(Args... args) {
    std::cout << "Przekazano " << sizeof...(args) << '\n';
}

template<typename Arg>
void showArgs(Arg arg) {
    std::cout << arg << '\n';
}

template<typename Arg, typename... Args>
void showArgs(Arg arg, Args... args) {
    std::cout << arg << ' ';
    showArgs(args...);
}

template<typename... Args>
struct MyClass: Args... {
};

int bar(int&& val) {
    std::cout << "bar() val = " << val << '\n';
    return val * 1233;
}

template<typename Function, typename... Args>
auto executor(Function&& fun, Args&&... args) -> typename std::result_of<Function(Args...)>::type {
    return std::forward<Function>(fun)(std::forward<Args>(args)...);
}

template<typename T1, typename T2>
auto myMax(T1 a, T2 b) -> decltype(a + b) {
    return a > b ? a: b;
}

int main() {
    foo(1, 2, 3, "ala", "zenon");
    showArgs(1, 2, 3, "ala", "zenon");
    int a = 434;
    //bar(std::move(a));
    auto result = executor(bar, std::move(a));
    std::cout << "result = " << result << '\n';
}
