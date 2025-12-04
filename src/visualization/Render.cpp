#include "../../include/visualization/Render.h"

Renderer::Renderer(Grid& g, int size)
    : grid(g), cellSize(size) {}

void Renderer::draw(sf::RenderWindow& window) {
    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));

    for (int r = 0; r < grid.rows; r++) {
        for (int c = 0; c < grid.cols; c++) {
            Node& n = grid.grid[r][c];

            // Color logic
            if (n.isWall)
                cell.setFillColor(sf::Color::Black);
            else if (n.visited)
                cell.setFillColor(sf::Color(100, 100, 255));
            else
                cell.setFillColor(sf::Color(200, 200, 200));
            if (n.isPath)
               cell.setFillColor(sf::Color::Yellow);


            // Start & goal
            if (r == 0 && c == 0)
                cell.setFillColor(sf::Color::Green);
            if (r == grid.rows - 1 && c == grid.cols - 1)
                cell.setFillColor(sf::Color::Red);

            // ⭐ FIXED: Set position using floats
           cell.setPosition(sf::Vector2f(
            c * cellSize,
            r * cellSize
           ));


            window.draw(cell);
        }
    }
}
