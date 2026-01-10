#pragma once
#include <SFML/Graphics.hpp>
#include "Algorithms/HeuristicMode.h" 
enum class EditMode {
    Walls,
    Terrain
};
struct InputState {
    bool runBFS = false;
    bool runDFS = false;
    bool runDijkstra = false;
    bool runAStar = false;

    bool resetGrid = false;
    bool leftClick = false;

    int mouseRow = -1;
    int mouseCol = -1;

    EditMode mode = EditMode::Walls;

    // ⭐ NEW (this is important)
    HeuristicMode heuristicMode = HeuristicMode::Admissible;
};
void processInput(
    sf::RenderWindow& window,
    const sf::Event& event,
    InputState& input,
    int cellSize
);
