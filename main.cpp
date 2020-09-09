#include <string>
#include <iostream>
#include <algorithm>
#include "RedBlackTree.h"
#include "TreePrinter.h"
#include <random>
#include "PQComplete.h"

class BaseCls {
public:
	virtual ~BaseCls() {
		std::cout << "~BaseCls()" << std::endl;
	}
};

class ExtCls : public BaseCls {
public:
	virtual ~ExtCls() {
		std::cout << "~ExtCls()" << std::endl;
	}
};

int main(int argc, char *argv[])
{
	PQComplete<int> pqi;
	pqi.insert(11);
	pqi.insert(21);
	pqi.insert(31);
	pqi.insert(89);
	pqi.insert(19);

	std::cout << pqi.delMax() << std::endl;
	std::cout << pqi.delMax() << std::endl;
	std::cout << pqi.delMax() << std::endl;
	std::cout << pqi.delMax() << std::endl;
	std::cout << pqi.delMax() << std::endl;
	std::cout << pqi.delMax() << std::endl;
	std::cout << pqi.delMax() << std::endl;
	return 0;
}
