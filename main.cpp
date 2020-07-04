#include <string>
#include <iostream>
#include "BinNode.h"


BinNodePosi(std::string)& test(BinNodePosi(std::string)& ptrRef) {
    return ptrRef -> lChild;
}


int main(int argc, char *argv[])
{
    BinNodePosi(std::string) node = new BinNode<std::string>("xunwu");

    BinNodePosi(std::string)& node2 = test(node);
    node2 = new BinNode<std::string>("it's ok");
    std::cout << node->data << std::endl;
    std::cout << node -> lChild->data << std::endl;
    return 0;
}
