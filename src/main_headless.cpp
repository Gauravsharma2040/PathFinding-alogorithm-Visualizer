#include <iostream>
#include <random>
#include "Grid.h"
#include "Algorithms/Astar.h"
#include "Algorithms/Dijkstra.h"
#include "Algorithms/HeuristicMode.h"
int main(int argc, char **argv)
{
    double sigma = 1.0;
    uint32_t seed = 12345;
    int rows = 40;
    int cols = 40;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--rows" && i + 1 < argc)
            rows = std::stoi(argv[++i]);
        else if (arg == "--cols" && i + 1 < argc)
            cols = std::stoi(argv[++i]);
        else if (arg == "--sigma" && i + 1 < argc)
            sigma = std::stod(argv[++i]);
        else if (arg == "--seed" && i + 1 < argc)
            seed = static_cast<uint32_t>(std::stoul(argv[++i]));
    }

    std::mt19937 rng(seed);

    Grid grid(rows, cols);

    while (true)
    {
        grid = Grid(rows, cols);             // fresh grid object
        grid.generateRandomWalls(0.20, rng); // new walls
        grid.applyNoise(sigma, rng);         // new noise

        grid.resetState();
        SearchStats tmp;
        Dijkstra(grid, grid.start, grid.goal, tmp);

        if (grid.goal->distance < std::numeric_limits<double>::infinity())
            break; // valid grid with path
    }

    SearchStats stats;

    // Dijkstra
    grid.resetState();
    Dijkstra(grid, grid.start, grid.goal, stats);
    std::cout << "Dijkstra, cost=" << grid.goal->distance
              << ", expanded=" << stats.expanded << "\n";

    auto runAStar = [&](const char *name, HeuristicMode mode)
    {
        stats = {};
        grid.resetState();
        AStar(grid, grid.start, grid.goal, mode, stats);
        std::cout << name
                  << ", cost=" << grid.goal->gCost
                  << ", expanded=" << stats.expanded << "\n";
    };

    runAStar("A*_zero", HeuristicMode::Zero);
    runAStar("A*_admissible", HeuristicMode::Admissible);
    runAStar("A*_noisy", HeuristicMode::Noisy);
    runAStar("A*_aggressive", HeuristicMode::Aggressive);

    return 0;
}
