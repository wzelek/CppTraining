#include <thread>
#include <iostream>

struct X {
    void operator()(int val) {
        std::cout << "X operator() val = " << val << '\n';
    }
};

struct Y {
    void run(int val) {
        std::cout << "X run() val = " << val << '\n';
    }
};

void foo(int& val) {
    ++val;
    std::cout << "foo() val = " << val << '\n';
}

int main() {
    int a = 10;
    X x;
    Y y;
    {
        std::thread thr1(foo, std::ref(a));
        std::thread thr2(x, 100);
        std::thread thr3(&Y::run, &y, 1000);
        std::thread thr4([](int val) { std::cout << "lambda val = " << val; }, 56);
        thr3.detach();
        for(auto& th: {&thr1, &thr2, &thr3, &thr4} ) {
            if(th->joinable()) {
                th->join();
            }
        }
    }
    std::cout << a << '\n';
}
