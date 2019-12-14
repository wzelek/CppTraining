#include <optional>
#include <iostream>

std::optional<int> foo(int a, int b) {
    if(b == 0) {
        return {};
    }
    return {a / b};
}

int main() {
    auto result = foo(12, 0);
    //result = std::make_optional<int>(200);
    //std::cout << result.value_or(100) << '\n';
    if(result.has_value()) {
        std::cout << *result << '\n';
    } else {
        std::cout << "Nie ma wyniku\n";
    }
}
