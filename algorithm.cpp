#include "Fibonacci.h"
#include "LCS.h"
#include <iostream>

class Test {
public:
    static int* ptr;
    static void init() {
        ptr = new int[10];
    }

    static void set(unsigned int p, int v) {
        ptr[p] = v;
    }

    static int get(unsigned int p) {
        return ptr[p];
    }

    static std::string test(const char* c) {
        return 'c' + std::string(c);
    }
};
int* Test::ptr = nullptr;

int main() {
    std::cout << LCS::recursive("educational", 11, "advantage", 9) << std::endl;
    std::cout << LCS::iterate("didactical", 10, "advantage", 9) << std::endl;
    std::cout << LCS::iterate("educational", 11, "advantage", 9) << std::endl;
    return 0;
}