#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.h"
#include <random>
#include "Algorithms/BFS.h"
#include "Algorithms/DFS.h"
#include "Algorithms/AStar.h"
#include "Algorithms/Dijkstra.h"
#include "utils/pathutils.h"
#include "visualization/Render.h"
#include "utils/input.h"

int main()
{
    struct AlgoResult
    {
        float cost = -1.f;
        int expanded = -1;
    };

    struct CostResults
    {
        AlgoResult dijkstra;
        AlgoResult noHeuristic;
        AlgoResult admissible;
        AlgoResult noisy;
        AlgoResult aggressive;
    };

    CostResults costs;

    enum class AlgoType
    {
        NONE,
        DIJKSTRA,
        ASTAR
    };

    AlgoType lastAlgo = AlgoType::NONE;
    float lastFinalCost = 0.0f;
    bool showFinalCost = false;
    // --------------------------
    // ANIMATION VARIABLES
    // --------------------------
    std::vector<Node *> animationOrder;
    int animIndex = 0;
    bool animating = false;

    std::vector<Node *> pathOrder;
    int pathIndex = 0;
    bool drawingPath = false;

    // --------------------------
    // GRID + RENDER SETUP~
    // --------------------------

    Grid grid(60,60);
    std::mt19937 rng(12345);
    grid.generateRandomWalls(0.20, rng);
    double sigma = 0.5;
    grid.applyNoise(sigma, rng);
    Renderer renderer(grid, 15);

    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned>(grid.cols * renderer.getCellSize()),
                       static_cast<unsigned>(grid.rows * renderer.getCellSize())}),
        "Pathfinding Visualizer");
    sf::Font font;
    if (!font.openFromFile("assets/fonts/Roboto-VariableFont_wdth,wght.ttf"))
    {
        std::cerr << "Failed to load font\n";
    }

    sf::Text finalCostText(font);
    finalCostText.setCharacterSize(18);
    finalCostText.setFillColor(sf::Color::White);
    finalCostText.setPosition(sf::Vector2f(10.f, 10.f));
    sf::RectangleShape hudBg;
    hudBg.setFillColor(sf::Color(0, 0, 0, 150)); 
    hudBg.setPosition(sf::Vector2f(5.f, 5.f));
    hudBg.setSize(sf::Vector2f(380.f, 180.f)); 

    // --------------------------
    // MAIN LOOP
    // --------------------------
    InputState input;
    SearchStats stats;
    while (window.isOpen())
    {

        while (const auto eventOpt = window.pollEvent())
        {
            const sf::Event &event = *eventOpt;

            if (event.is<sf::Event::Closed>())
            {
                window.close();
                break;
            }

            processInput(window, event, input, renderer.getCellSize());
        }

        // --------------------------
        // HANDLE INPUT FLAGS
        // --------------------------

        if (input.leftClick)
        {
            Node *n = grid.get(input.mouseRow, input.mouseCol);
            if (n && n != grid.start && n != grid.goal)
            {
                if (input.mode == EditMode::Walls)
                    n->isWall = !n->isWall;
                else if (input.mode == EditMode::Terrain)
                    grid.cycleTerrain(*n);
            }
            input.leftClick = false;
        }

        if (input.resetGrid)
        {
            grid.generateRandomWalls(0.20, rng);
            input.resetGrid = false;
        }
         
        // BFS
        if (input.runBFS)
        {
            grid.resetState();
            animationOrder = BFS(grid, grid.start, grid.goal);
            animIndex = 0;
            animating = true;
            drawingPath = false;
            input.runBFS = false;
        }
        // Dijkstra
        if (input.runDijkstra)
        {    
            stats = {}; 
            grid.resetState();
            animationOrder = Dijkstra(grid, grid.start, grid.goal,stats);

            animIndex = 0;
            animating = true;
            drawingPath = false;

            lastAlgo = AlgoType::DIJKSTRA;
            showFinalCost = false; 
            input.runDijkstra = false;
        }

        // A*
        if (input.runAStar)
        {   
            stats = {}; 
            grid.resetState();
            animationOrder = AStar(
                grid,
                grid.start,
                grid.goal,
                input.heuristicMode,
                stats
            );

            lastAlgo = AlgoType::ASTAR;
            showFinalCost = false; 

            animIndex = 0;
            animating = true;
            drawingPath = false;
            input.runAStar = false;
        }

        // --------------------------
        // ANIMATION STEP (visited nodes)
        // --------------------------
        if (animating)
        {
            if (animIndex < animationOrder.size())
            {
                Node *n = animationOrder[animIndex];
                n->visited = true;
                animIndex++;
            }
            else
            {
                animating = false;

                // Start path animation
                auto path = reconstructPath(grid.goal);
                pathOrder = path;
                pathIndex = 0;
                drawingPath = true;
            }
        }

        // --------------------------
        // ANIMATE FINAL PATH
        // --------------------------
        if (drawingPath)
        {
            if (pathIndex < pathOrder.size())
            {
                Node *p = pathOrder[pathIndex];
                p->isPath = true; 
                pathIndex++;
            }
            else
            {
                drawingPath = false;

                // ---- FINAL COST CAPTURE ----
                if (grid.goal)
                {
                    float finalCost = -1.f;

                    if (lastAlgo == AlgoType::DIJKSTRA)
                    {
                        finalCost = grid.goal->distance;
                        costs.dijkstra.cost = finalCost;
                        costs.dijkstra.expanded = stats.expanded;
                    }
                    else if (lastAlgo == AlgoType::ASTAR)
                    {
                        finalCost = grid.goal->gCost;

                        switch (input.heuristicMode)
                        {
                        case HeuristicMode::Zero:
                            costs.noHeuristic.cost = finalCost;
                            costs.noHeuristic.expanded = stats.expanded;
                            break;
                        case HeuristicMode::Admissible:
                            costs.admissible.cost = finalCost;
                            costs.admissible.expanded = stats.expanded;
                            break;
                        case HeuristicMode::Noisy:
                            costs.noisy.cost = finalCost;
                            costs.noisy.expanded = stats.expanded;
                            break;
                        case HeuristicMode::Aggressive:
                            costs.aggressive.cost = finalCost;
                            costs.aggressive.expanded = stats.expanded;
                            break;
                        }
                    }

                    if (finalCost >= 0)
                    {
                        lastFinalCost = finalCost;
                        showFinalCost = true;
                    }
                }
            }
            sf::FloatRect textBounds = finalCostText.getLocalBounds();
            hudBg.setSize(sf::Vector2f(
                textBounds.size.x + 20.f,
                textBounds.size.y + 20.f));
        }

        // --------------------------
        // DRAW EVERYTHING
        // --------------------------
        window.clear(sf::Color::White);
        renderer.draw(window);

        if (showFinalCost)
        {
            std::ostringstream oss;
            oss << "Path Cost Comparison\n";
            oss << "---------------------\n";

            auto printAlgo = [&](const std::string &name, const AlgoResult &r)
            {
                if (r.cost >= 0)
                {
                    oss << name << "\n";
                    oss << "  cost      : " << r.cost << "\n";
                    oss << "  expanded  : " << r.expanded << "\n\n";
                }
            };

            printAlgo("Dijkstra", costs.dijkstra);
            printAlgo("A* (h = 0)", costs.noHeuristic);
            printAlgo("A* (admissible)", costs.admissible);
            printAlgo("A* (noisy)", costs.noisy);
            printAlgo("A* (aggressive)", costs.aggressive);

            finalCostText.setString(oss.str());

            finalCostText.setOutlineColor(sf::Color::Black);
            finalCostText.setOutlineThickness(1.5f);

            sf::FloatRect textBounds = finalCostText.getLocalBounds();

            hudBg.setSize(sf::Vector2f(
                textBounds.size.x + 20.f,
                textBounds.size.y + 20.f));
            window.draw(hudBg);
            window.draw(finalCostText);
        }
        window.display();
    }

    return 0;
}
