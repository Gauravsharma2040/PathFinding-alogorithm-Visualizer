#pragma once

#include <vector>
#include "../Grid.h"
#include "../src/utils/input.h"   // for HeuristicMode
 
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
