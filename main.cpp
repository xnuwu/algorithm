#include <string>
#include <iostream>
#include <random>
#include "Splay.h"
#include <time.h>
#include "List.h"

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
    default_random_engine e;
    uniform_int_distribution<unsigned> u(0, 1000000);
    Splay<unsigned> avl;

    for (int i = 0; i < 1000000; i++) {
        avl.insert(u(e));
    }

    time_t seconds = time(nullptr);
    unsigned num;
    for (int i = 0; i < 1000; i++) {
        num = u(e);
        avl.search(num);
    }
    std::cout << "tree search cost time " << (time(nullptr) - seconds) << std::endl;

    List<unsigned> ulist;
    for (int i = 0; i < 1000000; i++) {
        ulist.insertAsFirst(u(e));
    }
    seconds = time(nullptr);
    ulist.sort();

    seconds = time(nullptr);
    for (int i = 0; i < 1000; i++) {
        num = u(e);
        ulist.search(num);
    }
    std::cout << "list search cost time " << (time(nullptr) - seconds) << std::endl;


}
