#pragma once

#include <SFML/Graphics.hpp>

enum Direction {
    X=1, Y=2,
};

class Scale {

public:

    static void reset();
    static void rescale(sf::Vector2u windowSize);

    static float getScale();
    static float getScaleRatio();

private:

    static float scale;
    static float scaleRatio;

};