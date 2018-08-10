#pragma once

#include <SFML/Graphics.hpp>

class TileConfig {

public:

    sf::Uint32 tileWidth = 16;
    sf::Uint32 tileHeight = 16;
    sf::Uint32 blocksOnHeight = 12;

    sf::Uint32 separatorX = 0;
    sf::Uint32 separatorY = 0;
    sf::Uint32 offsetX = 0;
    sf::Uint32 offsetY = 0;

};