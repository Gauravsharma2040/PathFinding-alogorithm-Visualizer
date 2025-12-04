#include "../../include/Algorithms/Dijkstra.h"
#include <queue>
#include <limits>

std::vector<Node*> Dijkstra(Grid& grid, Node* start, Node* goal) {
    std::vector<Node*> order;
    if (!start || !goal) return order;

    struct State { double dist; Node* node; };
    struct Cmp { bool operator()(State const& a, State const& b) const { return a.dist > b.dist; } };
    std::priority_queue<State, std::vector<State>, Cmp> pq;

    for (int r = 0; r < grid.rows; ++r)
        for (int c = 0; c < grid.cols; ++c)
            grid.grid[r][c].distance = INT_MAX;

    start->distance = 0;
    pq.push({0.0, start});

    while (!pq.empty()) {
        State s = pq.top(); pq.pop();
        Node* cur = s.node;
        if (cur->visited) continue;
        cur->visited = true;
        order.push_back(cur);
        if (cur == goal) break;

        for (Node* n : grid.getNeighbors(cur)) {
            if (n->isWall) continue;
            double nd = cur->distance + 1;
            if (nd < n->distance) {
                n->distance = static_cast<int>(nd);
                n->parent = cur;
                pq.push({nd, n});
            }
        }
    }
    return order;
}
