#include <iostream>
#include "PQLeftHeap.h"
#include <random>
#include <iomanip>
#include "String.h"

int main()
{
	const char* cstr = "xunwu is good";
	String str1(cstr, 13);

	std::cout << std::boolalpha << !str1 << std::endl;
	String str2 = str1.suffix(4);
	std::cout << str2 << std::endl;

	String str3 = str1.prefix(5);
	std::cout << str3 << std::endl;

	String str4 = str1.prefix(5);
	std::cout << std::boolalpha << (str3 == str4) << std::endl;

	std::cout << (str3.concat(str2)) << std::endl;
	return 0;
}