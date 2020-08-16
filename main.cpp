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
    RedBalckTree<int> rbtree;
    rbtree.insert(11);
    rbtree.insert(21);
    rbtree.insert(32);
    rbtree.insert(14);
    rbtree.insert(28);
    rbtree.insert(24);
    rbtree.insert(64);
    rbtree.insert(12);
    rbtree.insert(84);
    rbtree.insert(41);
    rbtree.insert(61);
    rbtree.insert(84);
    rbtree.insert(61);
    rbtree.insert(72);

    rbtree.remove(11);
    rbtree.remove(21);
    rbtree.remove(24);
    rbtree.remove(64);
    rbtree.remove(12);
    rbtree.remove(32);
    rbtree.remove(14);
    rbtree.remove(28);
    rbtree.remove(61);
    rbtree.remove(84);
    rbtree.remove(61);
    rbtree.remove(72);
    rbtree.remove(84);
    rbtree.remove(41);

    std::cout << "max " << std::max(11, 22) << std::endl;
}
