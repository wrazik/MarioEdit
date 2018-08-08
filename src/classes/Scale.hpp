#pragma once

#include <SFML/Graphics.hpp>

enum Direction {
    X=1, Y=2,
};

class Scale {

public:

    void rescale(sf::Vector2u windowSize);

    static float getScale();
    static float getScaleRatio();

private:

    const sf::Uint32 blocksOnHeight = 12;
    const sf::Uint32 blockHeight = 16;
    static float scale;
    static float scaleRatio;

};