#include <iostream>
#include <chrono>
#include "String.h"


int main() {

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	String str("yaangxunwu");
	String pat("xunwu");
	auto i = str.kmpMatch(pat);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << i << " cost time " << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)).count() << std::endl;
	return 0;
}