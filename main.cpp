#include <string>
#include <iostream>
#include <algorithm>
#include "RedBlackTree.h"

template<typename T>
class PrintTree {
public:
    void operator()(T& e) {
        std::cout << e << " ";
    }
};

int main(int argc, char *argv[])
{
   /* RedBalckTree<int> rbtree;
    IsBlack(rbtree.root());*/

    std::cout << "max " << std::max(11, 22) << std::endl;
}
