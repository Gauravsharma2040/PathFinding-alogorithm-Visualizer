#pragma once
#include <vector>
#include "../Grid.h"

std::vector<Node*> AStar(Grid& grid, Node* start, Node* goal);
