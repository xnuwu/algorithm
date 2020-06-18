#include <string>
#include <iostream>
#include "Vector.h"
#include "Bitmap.h"
#include "AdjListGraph.h"


int main(int argc, char *argv[])
{
    AdjListGraph<int, int> matrix;
    Vertex<int> vertex1(1);
    Vertex<int> vertex2(1);
    matrix.insert(10);
    matrix.insert(11);
    matrix.insert(12);
    std::cout << (matrix.n == 3) << std::endl;
    matrix.insert(100, 50, 0, 1);
    matrix.insert(101, 40, 0, 2);
    std::cout << (matrix.e == 2) << std::endl;
    matrix.insert(13);
    std::cout << (matrix.n == 4) << std::endl;
    std::cout << matrix.exists(0, 1) << std::endl;
    std::cout << matrix.exists(0, 2) << std::endl;
    std::cout << (matrix.exists(0, 3) == false ) << std::endl;
    std::cout << (matrix.e == 2) << std::endl;
    std::cout << (matrix.n == 4) << std::endl;

    std::cout << (matrix.inDegree(2) == 1) << std::endl;
    std::cout << (matrix.outDegree(0) == 2) << std::endl;
    std::cout << (matrix.edge(0, 1) == 100) << std::endl;
    std::cout << matrix.remove(0,1) << std::endl;
    std::cout << (matrix.exists(0, 1) == false) << std::endl;
    std::cout << (matrix.e == 1) << std::endl;
    std::cout << (matrix.n == 4) << std::endl;

    return 0;
}
