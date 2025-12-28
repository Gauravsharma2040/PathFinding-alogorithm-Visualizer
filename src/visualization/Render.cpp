#include "../../include/visualization/Render.h"

Renderer::Renderer(Grid& g, int size)
    : grid(g), cellSize(size) {}

void Renderer::draw(sf::RenderWindow& window) {
    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));

    for (auto& row : grid.grid) {
        for (auto& node : row) {

            // Base color
            if (node.isWall)
                cell.setFillColor(sf::Color::Black);
            else if (node.visited)
                cell.setFillColor(sf::Color(100, 100, 255));
            else
                cell.setFillColor(sf::Color(200, 200, 200));

            if (node.isPath)
                cell.setFillColor(sf::Color::Yellow);

            // Start & goal (FIXED)
            if (&node == grid.start)
                cell.setFillColor(sf::Color::Green);
            else if (&node == grid.goal)
                cell.setFillColor(sf::Color::Red);

            // Position (FIXED & clear)
           cell.setPosition(sf::Vector2f(
           static_cast<float>(node.c * cellSize),
           static_cast<float>(node.r * cellSize)
        ));



            window.draw(cell);
        }
    }
}

