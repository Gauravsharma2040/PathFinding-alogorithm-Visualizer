#pragma once
#include <vector>
#include "../Grid.h"

std::vector<Node*> Dijkstra(Grid& grid, Node* start, Node* goal);
