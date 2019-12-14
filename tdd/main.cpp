#include <iostream>
#include <string>
#include <cassert>
#include <limits>
#include <unordered_map>

std::string toWord(unsigned value) {
    static const std::unordered_map<unsigned, const char *> valToWord = {
        {0, "zero"}, {1, "jeden"}, {2, "dwa"}, {3, "trzy"}, {4, "cztery"},
        {5, "pięć"}, {6, "sześć"}, {7, "siedem"}, {8, "osiem"}, {9, "dziewięć"},
        {10, "dziesięć"}, {11, "jedenaście"}, {12, "dwanaście"},
        {13, "trzynaście"}, {14, "czternaście"}, {15, "piętnaście"},
        {16, "szesnaście"}, {17, "siedemnaście"}, {18, "osiemnaście"},
        {19, "dziewiętnaście"}, {20, "dwadzieścia"}, {30, "trzydzieści"},
        {40, "czterdzieści"}, {50, "pięćdziesiąt"}, {60, "sześćdziesiąt"},
        {70, "siedemdziesiąt"}, {80, "osiemdziesiąt"}, {90, "dziewięćdziesiąt"}
    };
    if(value > 99) {
        return "Błąd!";
    } else if(auto it = valToWord.find(value); it != valToWord.cend()) {
        return it->second;
    } else if(value % 10 != 0) {
        return toWord((value / 10 ) * 10) + " " + toWord(value % 10);
    }
    return "Błąd!";
}

void testMaxRange() {
    assert(toWord(0) == std::string("zero"));
    assert(toWord(std::numeric_limits<unsigned>::max()) == std::string("Błąd!"));
    assert(toWord(100) == std::string("Błąd!"));
}

void test0_9() {
    assert(toWord(0) == std::string("zero"));
    assert(toWord(1) == std::string("jeden"));
    assert(toWord(2) == std::string("dwa"));
    assert(toWord(3) == std::string("trzy"));
    assert(toWord(4) == std::string("cztery"));
    assert(toWord(5) == std::string("pięć"));
    assert(toWord(6) == std::string("sześć"));
    assert(toWord(7) == std::string("siedem"));
    assert(toWord(8) == std::string("osiem"));
    assert(toWord(9) == std::string("dziewięć"));
}

void testRounded10() {
    assert(toWord(10) == std::string("dziesięć"));
    assert(toWord(20) == std::string("dwadzieścia"));
    assert(toWord(30) == std::string("trzydzieści"));
    assert(toWord(40) == std::string("czterdzieści"));
    assert(toWord(50) == std::string("pięćdziesiąt"));
    assert(toWord(60) == std::string("sześćdziesiąt"));
    assert(toWord(70) == std::string("siedemdziesiąt"));
    assert(toWord(80) == std::string("osiemdziesiąt"));
    assert(toWord(90) == std::string("dziewięćdziesiąt"));
}

void test10_19() {
    assert(toWord(10) == std::string("dziesięć"));
    assert(toWord(11) == std::string("jedenaście"));
    assert(toWord(12) == std::string("dwanaście"));
    assert(toWord(13) == std::string("trzynaście"));
    assert(toWord(14) == std::string("czternaście"));
    assert(toWord(15) == std::string("piętnaście"));
    assert(toWord(16) == std::string("szesnaście"));
    assert(toWord(17) == std::string("siedemnaście"));
    assert(toWord(18) == std::string("osiemnaście"));
    assert(toWord(19) == std::string("dziewiętnaście"));
}

void testNotRounded10() {
    assert(toWord(16) == std::string("szesnaście"));
    assert(toWord(23) == std::string("dwadzieścia trzy"));
    assert(toWord(38) == std::string("trzydzieści osiem"));
    assert(toWord(41) == std::string("czterdzieści jeden"));
    assert(toWord(53) == std::string("pięćdziesiąt trzy"));
    assert(toWord(65) == std::string("sześćdziesiąt pięć"));
    assert(toWord(72) == std::string("siedemdziesiąt dwa"));
    assert(toWord(87) == std::string("osiemdziesiąt siedem"));
    assert(toWord(99) == std::string("dziewięćdziesiąt dziewięć"));
}

int main() {
    testMaxRange();
    test0_9();
    test10_19();
    testRounded10();
    testNotRounded10();
}
