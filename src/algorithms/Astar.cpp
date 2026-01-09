#include "../../include/Algorithms/AStar.h"
#include <queue>
#include <cmath>


static double heuristic(Node* a, Node* b, HeuristicMode mode) {
    int dx = std::abs(a->r - b->r);
    int dy = std::abs(a->c - b->c);

    switch (mode) {
        case HeuristicMode::Zero:
            return 0.0;

        case HeuristicMode::Admissible:
            return (dx + dy) * 1.0;

        case HeuristicMode::Noisy:
            return (dx + dy) * (1.0 + ((rand() % 20 - 10) / 100.0));

        case HeuristicMode::Aggressive:
            return (dx + dy) * 3.0;
    }

    return 0.0;
}


std::vector<Node*> AStar(
    Grid& grid,
    Node* start,
    Node* goal,
    HeuristicMode mode,
    SearchStats& stats
    
) {
    std::vector<Node*> order;
    if (!start || !goal) return order;

    auto cmp = [](Node* a, Node* b) {
        return a->fCost > b->fCost;
    };

    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> pq(cmp);

    start->gCost = 0.0;
    start->hCost = heuristic(start, goal, mode);
    start->fCost = start->gCost + start->hCost;
    pq.push(start);

    while (!pq.empty()) {
        Node* cur = pq.top();
        pq.pop();
        stats.expanded++;

        if (cur->visited) continue;
        cur->visited = true;
        order.push_back(cur);

        if (cur == goal) break;

        for (Node* n : grid.getNeighbors(cur)) {
            if (n->isWall) continue;

            double tentativeG = cur->gCost + n->trueCost;

            if (tentativeG < n->gCost) {
                n->parent = cur;
                n->gCost = tentativeG;
                n->hCost = heuristic(n, goal, mode);
                n->fCost = n->gCost + n->hCost;
                pq.push(n);
            }
        }
    }

    return order;
}
