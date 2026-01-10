#include "Algorithms/BFS.h"
#include <queue>

std::vector<Node*> BFS(Grid& grid, Node* start, Node* goal) {
    std::vector<Node*> order;
    if (!start || !goal) return order;

    std::queue<Node*> q;
    start->visited = true;
    start->distance = 0;
    q.push(start);

    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        order.push_back(cur);
        if (cur == goal) break;

        for (Node* n : grid.getNeighbors(cur)) {
            if (!n->visited && !n->isWall) {
                n->visited = true;
                n->parent = cur;
                n->distance = cur->distance + 1;
                q.push(n);
            }
        }
    }
    return order;
}
