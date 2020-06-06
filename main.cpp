
#include <iostream>
#include <string>
#include "Convert.h"
#include "ExpParen.h"
#include "ReversePolishNotation.h"

using std::string;

void test(char*& S) {
    S++;
    S++;
}

int main() {
    char cp[] = "12 + ( 4 + 25 ) / 3 * 5 * 67 - 8 + 9";
    char *rpn = new char[30];
    double ret = evaluate(cp, rpn);
    std::cout << ret << std::endl;
}
