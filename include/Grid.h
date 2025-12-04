#pragma once
#include "Node.h"
#include <vector>
#include <cstdlib>

class Grid {
public:
    int rows, cols;
    std::vector<std::vector<Node>> grid;

    Grid(int r, int c) : rows(r), cols(c) {
        grid.resize(rows, std::vector<Node>(cols));
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                grid[i][j] = Node(i, j);
    }

    Node* get(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) return nullptr;
        return &grid[r][c];
    }

    std::vector<Node*> getNeighbors(Node* n) {
        static int dirs[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
        std::vector<Node*> res;

        for (auto& d : dirs) {
            Node* next = get(n->r + d[0], n->c + d[1]);
            if (next && !next->isWall)
                res.push_back(next);
        }
        return res;
    }

    // ⭐ FIXED: This function must exist
    void generateRandomWalls(double density = 0.25) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
                // skip borders optionally
                grid[i][j].isWall = ((rand() % 100) < density * 100);
            }
    }

    void resetState() {
        for (auto& row : grid)
            for (auto& n : row) {
                n.visited = false;
                n.parent  = nullptr;
                n.gCost = 1e18;
                n.hCost = 0;
                n.fCost = 0;
                n.isPath = false;
            }
    }
};
