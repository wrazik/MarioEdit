#include "PositionCalc.hpp"

sf::Vector2u PositionCalc::windowSize = {0, 0};

void PositionCalc::setWindowSize(sf::Vector2u windowSize) {
    PositionCalc::windowSize = windowSize;
}

std::size_t PositionCalc::percent(float percent, Axis axis) {

    size_t calcFrom = PositionCalc::windowSize.y;
    if (axis == Axis::X) {
        calcFrom = PositionCalc::windowSize.x;
    }

    return (percent/100)*calcFrom;
}