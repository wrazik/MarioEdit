#include "Axis.hpp"

#include <vector>
#include <iostream>
#include "Tile.hpp"
#include "TileRegistry.hpp"

float Axis::scale = 1;

void Axis::rescale(sf::Vector2u windowSize) {
    float prevScale = Axis::scale;
    scale = (float)windowSize.y / (float)(blockHeight*blocksOnHeight);

    if (prevScale == Axis::scale) {
        return;
    }

    float scaleRatio = Axis::scale/prevScale;

    auto tiles = TileRegistry::getAll();
    for (int i=0; i<tiles.size(); i++) {
        auto tile = tiles.at(i);
        auto position = tile->getPosition();
        tile->setPosition(position.x*scaleRatio, position.y*scaleRatio);
    }
}

float Axis::getScale() {
    return Axis::scale;
}
