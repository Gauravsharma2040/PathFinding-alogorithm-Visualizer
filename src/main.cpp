#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Grid.h"
#include "../include/Algorithms/BFS.h"
#include "../include/Algorithms/DFS.h"
#include "../include/Algorithms/AStar.h"
#include "../include/Algorithms/Dijkstra.h"
#include "../src/utils/pathutils.h"
#include "../include/visualization/Render.h"

int main() {

    // --------------------------
    // ANIMATION VARIABLES
    // --------------------------
    std::vector<Node*> animationOrder;
    int animIndex = 0;
    bool animating = false;

    std::vector<Node*> pathOrder;
    int pathIndex = 0;
    bool drawingPath = false;

    // --------------------------
    // GRID + RENDER SETUP~
    // --------------------------
    Grid grid(20,20);
    grid.generateRandomWalls(0.20);

    Node* start = grid.get(0, 0);
    Node* goal  = grid.get(grid.rows - 1, grid.cols - 1);

    start->isWall = false;
    goal->isWall = false;

    Renderer renderer(grid, 30);

    sf::RenderWindow window(
        sf::VideoMode({
            static_cast<unsigned>(grid.cols * renderer.getCellSize()),
            static_cast<unsigned>(grid.rows * renderer.getCellSize())
        }),
        "Pathfinding Visualizer"
    );

    // --------------------------
    // MAIN LOOP
    // --------------------------
    while (window.isOpen()) {

        // EVENT HANDLING
        while (const auto eventOpt = window.pollEvent()) {
            const sf::Event& event = *eventOpt;

            // Close window
            if (event.is<sf::Event::Closed>()) {
                window.close();
                break;
            }

            // Mouse input (toggle walls)
            if (event.is<sf::Event::MouseButtonPressed>()) {
                const auto* mb = event.getIf<sf::Event::MouseButtonPressed>();
                if (mb && mb->button == sf::Mouse::Button::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    int col = mousePos.x / renderer.getCellSize();
                    int row = mousePos.y / renderer.getCellSize();

                    Node* n = grid.get(row, col);

                    if (n && !(row == 0 && col == 0) && !(row == grid.rows - 1 && col == grid.cols - 1)) {
                        n->isWall = !n->isWall;
                    }
                }
            }

            // Keyboard input
            if (event.is<sf::Event::KeyPressed>()) {
                const auto* kp = event.getIf<sf::Event::KeyPressed>();
                if (!kp) continue;

                // Reset walls
                if (kp->code == sf::Keyboard::Key::R) {
                    grid.generateRandomWalls(0.20);
                }

                // BFS
                if (kp->code == sf::Keyboard::Key::B) {
                    grid.resetState();
                    animationOrder = BFS(grid, start, goal);
                    animIndex = 0;
                    animating = true;
                    drawingPath = false;
                }

                // Dijkstra
                if (kp->code == sf::Keyboard::Key::D) {
                    grid.resetState();
                    animationOrder = Dijkstra(grid, start, goal);
                    animIndex = 0;
                    animating = true;
                    drawingPath = false;
                }

                // A*
                if (kp->code == sf::Keyboard::Key::A) {
                    grid.resetState();
                    animationOrder = AStar(grid, start, goal);
                    animIndex = 0;
                    animating = true;
                    drawingPath = false;
                }
                if (kp->code == sf::Keyboard::Key::C) {
                    grid.resetState();
                    animationOrder = DFS(grid, start, goal);
                    animIndex = 0;
                    animating = true;
                    drawingPath = false;
                }
            }
        }

        // --------------------------
        // ANIMATION STEP (visited nodes)
        // --------------------------
        if (animating) {
            if (animIndex < animationOrder.size()) {
                Node* n = animationOrder[animIndex];
                n->visited = true;
                animIndex++;
            }
            else {
                animating = false;

                // Start path animation
                auto path = reconstructPath(goal);
                pathOrder = path;
                pathIndex = 0;
                drawingPath = true;
            }
        }

        // --------------------------
        // ANIMATE FINAL PATH
        // --------------------------
        if (drawingPath) {
            if (pathIndex < pathOrder.size()) {
                Node* p = pathOrder[pathIndex];
                p->isPath = true; // you must add isPath to Node
                pathIndex++;
            }
            else {
                drawingPath = false;
            }
        }

        // --------------------------
        // DRAW EVERYTHING
        // --------------------------
        window.clear(sf::Color::White);
        renderer.draw(window);
        window.display();
    }

    return 0;
}
