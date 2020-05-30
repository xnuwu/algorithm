
#include <iostream>
#include "List.h"

void printIt(int& num) {
    std::cout << num << " ";
}

int main() {
    List<int> li;
    li.insertAsFirst(6);
    li.insertAsFirst(4);
    li.insertAsFirst(2);
    li.insertAsFirst(8);
    li.insertAsFirst(22);
    li.insertAsFirst(16);

    List<int> li2;
    li2.insertAsLast(7);
    li2.insertAsLast(5);
    li2.insertAsLast(25);
    li2.insertAsLast(3);
    li2.insertAsLast(1);
    li2.insertAsLast(11);

    li.merge(li2);
    li.sort();
    li.traverse(printIt);
}
