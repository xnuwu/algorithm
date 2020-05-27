
#include <iostream>
#include "ListNode.h"

void printIt(int& num) {
    std::cout << num << " ";
}

int main() {
    ListNode<int> i1(10);
    i1.insertAsPred(9);
    i1.insertAsSucc(11);
  
    std::cout << i1.data << std::endl;
    std::cout << i1.pred -> data << std::endl;
    std::cout << i1.succ -> data << std::endl;
}
