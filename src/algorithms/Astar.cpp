#include "../../include/Algorithms/AStar.h"
#include <queue>
#include <cmath>

static double heuristic(Node* a, Node* b) {
    return std::abs(a->r - b->r) + std::abs(a->c - b->c); //Manhatten Distance(admissable heuristic)
}

std::vector<Node*> AStar(Grid& grid, Node* start, Node* goal) {
    std::vector<Node*> order;
    if (!start || !goal) return order;

    auto cmp = [](Node* a, Node* b) { return a->fCost > b->fCost; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> pq(cmp);

    start->gCost = 0;
    start->hCost = heuristic(start, goal);
    start->fCost = start->gCost + start->hCost;
    pq.push(start);

    while (!pq.empty()) {
        Node* cur = pq.top(); pq.pop();
        if (cur->visited) continue;
        cur->visited = true;
        order.push_back(cur);
        if (cur == goal) break;

        for (Node* n : grid.getNeighbors(cur)) {
            if (n->isWall) continue;
            double tentativeG = cur->gCost + 1;
            if (!n->visited || tentativeG < n->gCost) {
                n->parent = cur;
                n->gCost = tentativeG;
                n->hCost = heuristic(n, goal);
                n->fCost = n->gCost + n->hCost;
                pq.push(n);
            }
        }
    }
    return order;
}
