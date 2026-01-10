#pragma once
#include <vector>
#include"Grid.h"
#include"Astar.h"
std::vector<Node*> Dijkstra(Grid& grid, Node* start, Node* goal,SearchStats& stats);
