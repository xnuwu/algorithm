#include <iostream>
#include "PQLeftHeap.h"
#include <random>
#include <iomanip>
#include "String.h"

int main()
{
	const char* cstr = "xunwu is good";
	String str1(cstr);

	std::cout << std::boolalpha << !str1 << std::endl;
	String str2 = str1.suffix(4);
	std::cout << str2 << std::endl;

	String str3 = str1.prefix(5);
	std::cout << str3 << std::endl;

	String str4 = str1.prefix(5);
	std::cout << std::boolalpha << (str3 == str4) << std::endl;
	std::cout << (str3.concat(str2)) << std::endl;

	String sub("unw1");
	std::cout << str1.substr(1, 3).equal(sub) << std::endl;


	std::cout << str1.match1("x") << std::endl;
	std::cout << str1.match1("d") << std::endl;
	std::cout << str1.match1("xu") << std::endl;
	std::cout << str1.match1("ood") << std::endl;

	std::cout << str1.match2("x") << std::endl;
	std::cout << str1.match2("d") << std::endl;
	std::cout << str1.match2("xu") << std::endl;
	std::cout << str1.match2("ood") << std::endl;
	
	std::cout << std::endl;
	std::cout << str1.match("x") << std::endl;
	std::cout << str1.match("d") << std::endl;
	std::cout << str1.match("xu") << std::endl;
	std::cout << str1.match("ood") << std::endl;

	return 0;
}