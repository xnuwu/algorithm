#include <string>
#include <iostream>
#include "Splay.h"

template<typename T>
class PrintTree {
public:
    void operator()(T& e) {
        std::cout << e << " ";
    }
};

int main(int argc, char *argv[])
{

    PrintTree<int> pavl;

    Splay<int> avl;
    avl.insert(1);
    avl.insert(2);
    avl.insert(3);
    avl.insert(4);
    avl.insert(5);
    avl.insert(10);
    avl.insert(9);
    avl.insert(8);
    avl.insert(7);
    avl.insert(12);
    avl.insert(15);
    avl.insert(6);

    avl.root() ->travInI3(avl.root(), pavl);
    avl.remove(10);

    std::cout << std::endl;
    avl.root()->travInI3(avl.root(), pavl);
    std::cout << std::endl;

    avl.insert(10);
    avl.insert(11);
    avl.insert(15);
    avl.insert(0);
    avl.insert(-10);
    avl.insert(110);
    avl.root()->travInI3(avl.root(), pavl);
    std::cout << std::endl;
}
