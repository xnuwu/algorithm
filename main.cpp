#include <string>
#include <iostream>
#include "Vector.h"
#include "Bitmap.h"
#include "GraphMatrix.h"


int main(int argc, char *argv[])
{
    GraphMatrix<int, int> matrix;
    Vertex<int> vertex1(1);
    Vertex<int> vertex2(1);
    matrix.insert(10);
    matrix.insert(11);
    matrix.insert(12);
    matrix.insert(100, 50, 0, 1);
    matrix.insert(101, 40, 0, 2);
    std::cout << matrix.exists(0, 1) << std::endl;
    std::cout << matrix.exists(0, 2) << std::endl;
    std::cout << matrix.e << std::endl;
    std::cout << matrix.n << std::endl;

    std::cout << matrix.inDegree(2) << std::endl;
    std::cout << matrix.outDegree(0) << std::endl;
    std::cout << matrix.edge(0,1) << std::endl;
    std::cout << matrix.remove(0,1) << std::endl;
    std::cout << matrix.exists(0,1) << std::endl;
    std::cout << matrix.e << std::endl;
    std::cout << matrix.n << std::endl;

    return 0;
}
