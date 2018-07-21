#pragma once

#include <SFML/Graphics.hpp>

enum Direction {
    X=1, Y=2,
};

class Axis {

public:

    void rescale(sf::Vector2u windowSize);

    std::size_t percent(float percent, Direction axis);
    static float getScale();

private:

    sf::Vector2u windowSize = {0, 0};
    const std::size_t blocksOnHeight = 12;
    const std::size_t blockHeight = 16;
    static float scale;

};