#pragma once
#include <SFML/Graphics.hpp>
#include "../Grid.h"

class Renderer {
private:
    Grid& grid;
    int cellSize;
public:
    Renderer(Grid& g, int size = 30);

    void draw(sf::RenderWindow& window);

    int getCellSize() const { return cellSize; }
};
