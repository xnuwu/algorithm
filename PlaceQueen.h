#pragma once

#include <iostream>
#include "Stack.h"

class Queen {
public:
    int x, y;
    Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {};

    bool operator==(Queen const& q) const {
        return x == q.x || y == q.y || (x + y == q.x + q.y) || (x - y == q.x - q.y);
    }

    bool operator!=(Queen const& q) const {
        return !(*this == q);
    }
};

void printQueen(Stack<Queen> solutions) {
    int size = solutions.size();
    for (int i = size - 1; 0 <= i; i--) {
        for (int j = 0; j < size; j++) {
            if (j == solutions.top().x && i == solutions.top().y) {
                solutions.pop();
                std::cout << "*  ";
            }
            else {
                std::cout << "[] ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void placeQueen(int N = 8) {
    Stack<Queen> solutions;
    Queen q(0, 0);
    do {
        if (q.x >= N || solutions.size() >= N) {
            q = solutions.pop();
            q.x++;
        }
        else {
            while ((q.x < N) && (0 <= solutions.find(q))) {
                q.x++;
            }
            if (q.x < N) {
                solutions.push(q);
                if(N <= solutions.size()) {
                    printQueen(solutions);
                }
                q.y++;
                q.x = 0;
            }
        }
    } while (q.x < N || 0 < q.y);
}

