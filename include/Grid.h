#pragma once
#include "Node.h"
#include <vector>
#include <cstdlib>
#include<random>
class Grid {
public:
    int rows, cols;
    std::vector<std::vector<Node>> grid; 
    Node* start = nullptr;
    Node* goal  = nullptr;
    void setTerrain(Node& n, TerrainType type);
    void cycleTerrain(Node& n);
    void applyNoise(double sigma, std::mt19937& rng);
    void setStart(int r, int c);
    void setGoal(int r, int c);

    Grid(int r, int c);

    Node* get(int r, int c);

    std::vector<Node*> getNeighbors(Node* n);

    // ⭐ FIXED: This function must exist
    void generateRandomWalls(double density, std::mt19937& rng);
    void resetState();
};
