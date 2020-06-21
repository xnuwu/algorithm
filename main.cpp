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
    graph.insert('I');  //8
    graph.insert('J');  //9

    graph.insert("AB", 0, 0, 1);
    graph.insert("AI", 0, 0, 8);
    graph.insert("AJ", 0, 0, 9);

    graph.insert("BA", 0, 1, 0);
    graph.insert("BC", 0, 1, 2);

    graph.insert("CB", 0, 2, 1);
    graph.insert("CH", 0, 2, 7);
    graph.insert("CD", 0, 2, 3);
    
    graph.insert("DC", 0, 3, 2);
    graph.insert("DE", 0, 3, 4);
    graph.insert("DG", 0, 3, 6);

    graph.insert("ED", 0, 4, 3);
    graph.insert("EJ", 0, 4, 9);

    graph.insert("FG", 0, 5, 6);

    graph.insert("GD", 0, 6, 3);
    graph.insert("GE", 0, 6, 4);
    graph.insert("GF", 0, 6, 5);

    graph.insert("HA", 0, 7, 0);
    graph.insert("HC", 0, 7, 2);

    graph.insert("IA", 0, 8, 0);
    graph.insert("IJ", 0, 8, 9);

    graph.insert("JI", 0, 9, 8);
    graph.insert("JA", 0, 9, 0);

    graph.bcc(0);
    return 0;
}
