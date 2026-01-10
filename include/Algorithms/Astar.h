#pragma once
#include <vector>
#include "Grid.h"
#include "Algorithms/HeuristicMode.h"
struct SearchStats
    {
        int expanded = 0;
    };
std::vector<Node*> AStar(
    Grid& grid,
    Node* start,
    Node* goal,
    HeuristicMode mode,
    SearchStats& stats
);
