#pragma once
#include "Node.h"
#include <vector>
#include <algorithm>

std::vector<Node*> reconstructPath(Node* goal) {
    std::vector<Node*> path;
    Node* cur = goal;

    while (cur != nullptr) {
        path.push_back(cur);
        cur = cur->parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}
