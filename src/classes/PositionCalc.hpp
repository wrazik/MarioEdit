#pragma once

#include <SFML/Graphics.hpp>

enum Axis {
    X=1, Y=2,
};

class PositionCalc {

public:

    static void setWindowSize(sf::Vector2u windowSize);

    std::size_t percent(float percent, Axis axis);

private:

    static sf::Vector2u windowSize;

};