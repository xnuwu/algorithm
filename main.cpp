#include <string>
#include <iostream>
#include <algorithm>
#include "RedBlackTree.h"
#include "TreePrinter.h"
#include <random>
#include "PQComplete.h"
#include "PQLeftHeap.h"

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
	return 0;
}
