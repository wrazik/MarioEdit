#include "Axis.hpp"

#include <vector>
#include "Tile.hpp"
#include "TileRegistry.hpp"

float Axis::scale = 0;

void Axis::rescale(sf::Vector2u windowSize) {
    this->windowSize = windowSize;

    float prevScale = this->scale;
    this->scale = (float)windowSize.y / (float)(this->blockHeight*this->blocksOnHeight);
    float scaleRatio = this->scale/prevScale;

    auto tiles = TileRegistry::getAll();
    for (int i=0; i<tiles.size(); i++) {
        auto tile = tiles.at(i);
        auto position = tile->getPosition();
        tile->setPosition(position.x*scaleRatio, position.y*scaleRatio);
    }
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
