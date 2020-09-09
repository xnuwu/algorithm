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
	Vector<int> vi;
	vi.insert(11);
	vi.insert(3);
	vi.insert(41);
	vi.insert(15);
	vi.insert(64);
	vi.insert(25);
	vi.sort();
	for (int i = 0; i < vi.size(); i++) {
		std::cout << vi[i] << std::endl;
	}
	return 0;
}
