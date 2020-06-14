#include <string>
#include <iostream>
#include <queue>
#include <map>
#include "Huffman.h"
#include "Bitmap.h"

using namespace std;

int main(int argc, char *argv[])
{
    HuffmanForest forest = readFileCharFrequency("D://temp/I_Have_A_Dream.txt");
    for (int i = 0; i < forest.size(); i++) {
        cout << (char)forest[i]->getData() << "[" << forest[i]->getData() << "]" << "=>" << forest[i]->getWeight() << endl;
    }
    cout << endl;
    HuffmanTree<int>* codeTree = buildHuffmanCodeTree(forest);
    HuffmanCodeTable table;
    Bitmap bitmap;
    int bitIndex = 0;
    genHuffmanCodeTable(table, bitmap, bitIndex, codeTree->treePtr->root());
    for (std::map<int, std::string>::iterator itr = table.begin(); itr != table.cend(); itr++) {
        std::cout << (char)itr->first << "[" << itr->first << "]" << "=>" << itr->second << std::endl;
    }

    std::string compressedFilename = compressFile(table, "D:/temp/I_Have_A_Dream.txt");
    BinNode<int> * root = codeTree->treePtr->root();
    decompressFile(root, compressedFilename);

   
    return 0;
}
