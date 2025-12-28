#pragma once
#include <limits>

enum class TerrainType {
    Normal,
    Rough,
    Water
};

struct Node {
    int r, c;

    bool isWall = false;
    bool visited = false;
    bool isPath = false;

    double gCost = std::numeric_limits<double>::infinity();
    double hCost = 0.0;
    double fCost = 0.0;

    double distance = std::numeric_limits<double>::infinity();
    double trueCost = 1.0;
    double noisyCost = 1.0;

    Node* parent = nullptr;
    TerrainType terrain = TerrainType::Normal;

    Node(int row = 0, int col = 0) : r(row), c(col) {}
};
