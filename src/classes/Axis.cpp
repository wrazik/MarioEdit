#include "Axis.hpp"

float Axis::scale = 0;

void Axis::rescale(sf::Vector2u windowSize) {
    this->windowSize = windowSize;
    this->scale = (float)windowSize.y / (float)(this->blockHeight*this->blocksOnHeight);
}

std::size_t Axis::percent(float percent, Direction axis) {

    size_t calcFrom = this->windowSize.y;
    if (axis == Direction::X) {
        calcFrom = this->windowSize.x;
    }

    return (percent/100)*calcFrom;
}

float Axis::getScale() {
    return Axis::scale;
}
