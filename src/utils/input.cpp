#include "input.h"
#include <SFML/Graphics.hpp>

void processInput(
    sf::RenderWindow &window,
    const sf::Event &event,
    InputState &input,
    int cellSize)
{
    // Mouse click
    if (event.is<sf::Event::MouseButtonPressed>())
    {
        const auto *mb = event.getIf<sf::Event::MouseButtonPressed>();
        if (mb && mb->button == sf::Mouse::Button::Left)
        {
            auto mousePos = sf::Mouse::getPosition(window);
            input.mouseCol = mousePos.x / cellSize;
            input.mouseRow = mousePos.y / cellSize;
            input.leftClick = true;
        }
    }

    // Keyboard
    if (event.is<sf::Event::KeyPressed>())
    {
        const auto *kp = event.getIf<sf::Event::KeyPressed>();
        if (!kp)
            return;

        switch (kp->code)
        {
        case sf::Keyboard::Key::R:
            input.resetGrid = true;
            break;
        case sf::Keyboard::Key::B:
            input.runBFS = true;
            break;
        case sf::Keyboard::Key::C:
            input.runDFS = true;
            break;
        case sf::Keyboard::Key::D:
            input.runDijkstra = true;
            break;
        case sf::Keyboard::Key::A:
            input.runAStar = true;
            break;
        case sf::Keyboard::Key::T:
            input.mode = EditMode::Terrain;
            break;
        case sf::Keyboard::Key::W:
            input.mode = EditMode::Walls;
            break;
        default:
            break;
        case sf::Keyboard::Key::Num1:
            input.heuristicMode = HeuristicMode::Zero;
            break;

        case sf::Keyboard::Key::Num2:
            input.heuristicMode = HeuristicMode::Admissible;
            break;

        case sf::Keyboard::Key::Num3:
            input.heuristicMode = HeuristicMode::Noisy;
            break;

        case sf::Keyboard::Key::Num4:
            input.heuristicMode = HeuristicMode::Aggressive;
            break;
        }
    }
}
