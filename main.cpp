#include <string>
#include <iostream>
#include "Vector.h"
#include "Bitmap.h"
#include "AdjListGraph.h"


int main(int argc, char *argv[])
{
    AdjListGraph<char, const char*> graph;
    graph.insert('A');  //0
    graph.insert('B');  //1
    graph.insert('C');  //2
    graph.insert('D');  //3
    graph.insert('E');  //4
    graph.insert('F');  //5
    graph.insert('G');  //6
    graph.insert('H');  //7

    graph.insert("AB", 4, 0, 1);
    graph.insert("AD", 6, 0, 3);
    graph.insert("AG", 7, 0, 6);

    graph.insert("BA", 6, 3, 0);
    graph.insert("BC", 12, 3, 2);

    graph.insert("CB", 12, 3, 2);
    graph.insert("CD", 9, 2, 3);
    graph.insert("CE", 1, 2, 4);
    graph.insert("CF", 2, 2, 5);
    graph.insert("CH", 10, 2, 7);

    graph.insert("DA", 6, 3, 0);
    graph.insert("DG", 2, 3, 6);
    graph.insert("DC", 9, 3, 2);

    graph.insert("EC", 1, 4, 2);
    graph.insert("EF", 5, 4, 5);
    graph.insert("EH", 8, 4, 7);

    graph.insert("FC", 2, 5, 2);
    graph.insert("FE", 5, 5, 4);

    graph.insert("GA", 7, 6, 0);
    graph.insert("GD", 2, 6, 3);
    graph.insert("GH", 14, 6, 7);

    graph.insert("HC", 10, 7, 2);
    graph.insert("HE", 8, 7, 4);
    graph.insert("HG", 14, 7, 6);

    graph.bfs(0);

    std::cout << std::endl;
    graph.dijkstra(0);

    std::cout << std::endl;
    graph.prim(0);

    return 0;
}
