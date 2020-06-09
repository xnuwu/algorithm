#include <iostream>
#include "BinTree.h"

int main(int argc, char* argv[]) {
    BinTree<int> bi;
    bi.insertAsRoot(10);
    bi.insertAsLC(bi.root(), 5);
    bi.insertAsRC(bi.root(), 15);
    std::cout << bi.root()->data << std::endl;
    std::cout << bi.root()->lChild->data << std::endl;
    std::cout << bi.root()->rChild->data << std::endl;
    return 0;
}