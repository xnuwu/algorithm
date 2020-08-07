#include <string>
#include <iostream>
#include "BTree.h"

template<typename T>
class PrintTree {
public:
    void operator()(T& e) {
        std::cout << e << " ";
    }
};

int main(int argc, char *argv[])
{
    BTree<int> bt(5);
    bt.insert(1);
    bt.insert(2);
    bt.insert(3);
    bt.insert(4);
    bt.insert(10);
    bt.insert(11);
    bt.insert(12);
    bt.insert(13);
}
