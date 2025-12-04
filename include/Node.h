#pragma once
#include <limits>
#include<climits>
struct Node {
    int r, c;
    bool isWall = false;
    bool visited = false;
    double gCost = std::numeric_limits<double>::infinity();
    double hCost = 0;
    double fCost = 0;
    Node* parent = nullptr;
    int distance = INT_MAX;
    bool isPath = false;


    Node(int row=0, int col=0) : r(row), c(col) {}
};
