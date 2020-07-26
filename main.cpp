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
    Vector<int> vi;
    vi.insert(1);
    vi.insert(2);
    vi.insert(3);
    vi.insert(4);
    vi.insert(5);
    vi.insert(6);

    std::cout << vi.search(11) << std::endl;
}
