#pragma once

#include <SFML/Graphics.hpp>

enum Direction {
    X=1, Y=2,
};

class Axis {

public:

    void rescale(sf::Vector2u windowSize);

    static float getScale();

private:

    const std::size_t blocksOnHeight = 12;
    const std::size_t blockHeight = 16;
    static float scale;

};