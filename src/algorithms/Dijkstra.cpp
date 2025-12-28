#include "../../include/Algorithms/Dijkstra.h"
#include <queue>
#include <limits>
#include "../../include/Algorithms/Dijkstra.h"
#include <queue>
#include <limits>

std::vector<Node *> Dijkstra(Grid &grid, Node *start, Node *goal,SearchStats& stats)
{
    std::vector<Node *> order;
    if (!start || !goal)
        return order;

    struct State
    {
        double dist;
        Node *node;
    };

    struct Cmp
    {
        bool operator()(const State &a, const State &b) const
        {
            return a.dist > b.dist;
        }
    };

    std::priority_queue<State, std::vector<State>, Cmp> pq;

    // Assume grid.resetState() was called before this
    start->distance = 0.0;
    pq.push({0.0, start});

    while (!pq.empty())
    {
        State s = pq.top();
        pq.pop();
        stats.expanded++;

        Node *cur = s.node;
        if (cur->visited)
            continue;

        cur->visited = true;
        order.push_back(cur);

        if (cur == goal)
            break;

        for (Node *n : grid.getNeighbors(cur))
        {
            if (n->isWall)
                continue;

            double nd = cur->distance + n->trueCost; // ⭐ WEIGHTED COST

            if (nd < n->distance)
            {
                n->distance = nd;
                n->parent = cur;
                pq.push({nd, n});
            }
        }
    }

    return order;
}
