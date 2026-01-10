#include <iostream>
#include <random>
#include "Grid.h"
#include "Algorithms/Astar.h"
#include "Algorithms/Dijkstra.h"
#include "Algorithms/HeuristicMode.h"
int main(int argc, char** argv)
{
    double sigma = 1.0;
    uint32_t seed = 12345;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--sigma" && i + 1 < argc) sigma = std::stod(argv[++i]);
        if (arg == "--seed"  && i + 1 < argc) seed  = std::stoul(argv[++i]);
    }

    Grid grid(100, 100);
    std::mt19937 rng(seed);

    grid.generateRandomWalls(0.20, rng);
    grid.applyNoise(sigma, rng);

    SearchStats stats;

    // Dijkstra
    grid.resetState();
    Dijkstra(grid, grid.start, grid.goal, stats);
    std::cout << "Dijkstra, cost=" << grid.goal->distance
              << ", expanded=" << stats.expanded << "\n";

    auto runAStar = [&](const char* name, HeuristicMode mode)
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
