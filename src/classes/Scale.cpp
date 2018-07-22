#include "Scale.hpp"

#include <vector>
#include <iostream>
#include "Tile.hpp"
#include "TileRegistry.hpp"

float Scale::scale = 1.0f;
float Scale::scaleRatio = 1.0f;

void Scale::rescale(sf::Vector2u windowSize) {
    float prevScale = Scale::scale;
    scale = (float)windowSize.y / (float)(blockHeight*blocksOnHeight);

    if (prevScale == Scale::scale) {
        return;
    }

    scaleRatio = Scale::scale/prevScale;
}

float Scale::getScale() {
    return Scale::scale;
}

float Scale::getScaleRatio() {
    return Scale::scaleRatio;
}
