#include "Grid.h"

#include <random>
#include <algorithm>
#include <vector>
#include <cstdlib> // rand()

// ---------------- CONSTRUCTOR ----------------

Grid::Grid(int r, int c) : rows(r), cols(c)
{
    grid.resize(rows, std::vector<Node>(cols));

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            grid[i][j] = Node(i, j);

    start = &grid[0][0];
    goal = &grid[rows - 1][cols - 1];

    start->isWall = false;
    goal->isWall = false;
}

// ---------------- START / GOAL ----------------

void Grid::setStart(int r, int c)
{
    if (start)
        start->isWall = false;
    start = get(r, c);
    start->isWall = false;
}

void Grid::setGoal(int r, int c)
{
    if (goal)
        goal->isWall = false;
    goal = get(r, c);
    goal->isWall = false;
}

// ---------------- TERRAIN ----------------

void Grid::setTerrain(Node &n, TerrainType type)
{
    n.terrain = type;

    switch (type)
    {
    case TerrainType::Normal:
        n.trueCost = 1.0;
        break;
    case TerrainType::Rough:
        n.trueCost = 3.0;
        break;
    case TerrainType::Water:
        n.trueCost = 8.0;
        break;
    }

    n.noisyCost = n.trueCost;
}

void Grid::cycleTerrain(Node &n)
{
    if (n.isWall)
        return;

    if (n.terrain == TerrainType::Normal)
        setTerrain(n, TerrainType::Rough);
    else if (n.terrain == TerrainType::Rough)
        setTerrain(n, TerrainType::Water);
    else
        setTerrain(n, TerrainType::Normal);
}

// ---------------- NOISE ----------------

void Grid::applyNoise(double sigma, std::mt19937 &rng)
{
    if (sigma <= 0.0)
    {
        for (auto &row : grid)
            for (auto &n : row)
                if (!n.isWall)
                    n.noisyCost = n.trueCost;

        return;
    }
    std::normal_distribution<double> dist(0.0, sigma);

    for (auto &row : grid)
    {
        for (auto &n : row)
        {
            if (!n.isWall)
            {
                n.noisyCost = std::max(0.1, n.trueCost + dist(rng));
            }
        }
    }
}

// ---------------- ACCESSORS ----------------

Node *Grid::get(int r, int c)
{
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        return nullptr;
    return &grid[r][c];
}

std::vector<Node *> Grid::getNeighbors(Node *n)
{
    static int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::vector<Node *> res;

    for (auto &d : dirs)
    {
        Node *next = get(n->r + d[0], n->c + d[1]);
        if (next && !next->isWall)
            res.push_back(next);
    }
    return res;
}

// ---------------- GRID STATE ----------------

void Grid::generateRandomWalls(double density, std::mt19937 &rng)
{
    std::bernoulli_distribution wall(density);

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            grid[i][j].isWall = wall(rng);

    // Always keep start / goal valid
    start->isWall = false;
    goal->isWall = false;
}

void Grid::resetState()
{
    for (auto &row : grid)
        for (auto &n : row)
        {
            n.visited = false;
            n.parent = nullptr;
            n.gCost = std::numeric_limits<double>::infinity();
            n.hCost = 0.0;
            n.fCost = 0.0;
            n.isPath = false;
            n.distance = std::numeric_limits<double>::infinity();
        }
}
