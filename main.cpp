#include <string>
#include <iostream>
#include "Vector.h"
#include "Bitmap.h"
#include "AdjListGraph.h"


int main(int argc, char *argv[])
{
   
    AdjListGraph<char, const char*> graph;
    graph.insert('A');
    graph.insert('B');
    graph.insert('C');
    graph.insert('D');
    graph.insert('E');
    graph.insert('F');
    graph.insert('G');
    graph.insert('S');

    graph.insert("AE", 0, 0, 4);
    graph.insert("AC", 0, 0, 2);
    graph.insert("CB", 0, 2, 1);
    graph.insert("DB", 0, 3, 1);
    graph.insert("EG", 0, 4, 6);
    graph.insert("EF", 0, 4, 5);
    graph.insert("GF", 0, 6, 5);
    graph.insert("GB", 0, 6, 1);
    graph.insert("SD", 0, 7, 3);
    graph.insert("SC", 0, 7, 2);
    graph.insert("SA", 0, 7, 0);

    graph.bcc(0);
    return 0;
}
