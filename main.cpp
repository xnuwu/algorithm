#include <string>
#include <iostream>
#include <queue>
#include "Huffman.h"
#include "Bitmap.h"

using namespace std;

int main(int argc, char *argv[])
{
    Bitmap bitmap(12);
    bitmap.set(5);
    bitmap.set(1);
    bitmap.set(2);
    bitmap.set(3);
    bitmap.set(4);
    bitmap.set(12);
    bitmap.dump("D:\\dump.bin");
    cout << bitmap.toString(20) << endl;
    Bitmap bitfile("D:\\dump.bin", 50);
    cout << bitfile.toString(20) << endl;
    return 0;
}