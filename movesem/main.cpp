#include <iostream>
#include <string>

struct X {
    explicit X(const std::string& name_)
      : name{new std::string(name_)} {
        std::cout << "Constructor X name = " << name_ << '\n';
    }
    X(const X& src) {
        std::cout << "Copy constructor X name = " << (src.name == nullptr ? "nullptr": *(src.name)) << '\n';
        name = new std::string(*(src.name));
    }
    X& operator=(const X& src) {
        std::cout << "operator= X old name = " << (name == nullptr ? "nullptr": *name) << " new name = "
          << (src.name == nullptr ? "nullptr": *(src.name)) << '\n';
        if(this != &src) {
            delete name;
            name = nullptr;
            if(src.name != nullptr) {
                name = new std::string(*(src.name));
            }
        }
        return *this;
    }
    X(X&& src) {
        std::cout << "Move constructor new name = " << (src.name  == nullptr ? "nullptr": *(src.name)) << '\n';
        name = src.name;
        src.name = nullptr;
    }
    void info() const {
        std::cout << "X name = " << (name == nullptr ? "nullptr": *name) << '\n';
    }
    ~X() {
        std::cout << "~X name = " << (name == nullptr ? "nullptr": *name) << '\n';
        delete name;
    }
private:
    std::string * name;
};

int main() {
    X x1{"Ala"};
    X x2{"Tola"};
    x1 = std::move(x2);
    X x3{std::move(x1)};
}
