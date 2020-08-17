#include <string>
#include <iostream>
#include <algorithm>
#include "RedBlackTree.h"
#include "TreePrinter.h"

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
    rbtree.insert(31);
    rbtree.insert(64);
    rbtree.insert(85);
    rbtree.insert(29);
    rbtree.insert(94);

    TreePrinter<int> tp;
    tp.printTree(rbtree.root());
}
