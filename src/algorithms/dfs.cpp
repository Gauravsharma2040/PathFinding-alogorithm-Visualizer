#include "Algorithms/DFS.h"
#include <stack>

std::vector<Node*> DFS(Grid& grid, Node* start, Node* goal) {
    std::vector<Node*> order;
    if (!start || !goal) return order;

    std::stack<Node*> st;
    st.push(start);
    start->visited = true;

    while (!st.empty()) {
        Node* cur = st.top(); st.pop();
        order.push_back(cur);
        if (cur == goal) break;

        for (Node* n : grid.getNeighbors(cur)) {
            if (!n->visited && !n->isWall) {
                n->visited = true;
                n->parent = cur;
                st.push(n);
            }
        }
    }
    return order;
}
