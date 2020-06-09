#include <iostream>
#include "BinTree.h"

template <typename T>
class Print {
public:
    void operator()(T e) {
        std::cout << e << std::endl;
    }
};

int main(int argc, char *argv[])
{
    BinTree<int> bi;
    Print<int> pi;
    bi.insertAsRoot(10);
    bi.insertAsLC(bi.root(), 5);
    bi.insertAsRC(bi.root(), 15);
    bi.insertAsLC(bi.root()->lChild, 2);
    bi.insertAsRC(bi.root()->rChild, 17);
    
    std::cout << std::endl;
    bi.root()->travInI3(bi.root(), pi);
    
    return 0;
}