#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "TileConfig.hpp"
#include "Tile.hpp"

class TileSet
{

public:

    TileSet(std::string filepath);

    void setTileSeparators(sf::Uint32 separatorX, sf::Uint32 separatorY);
    void setTileOffset(sf::Uint32 offsetX, sf::Uint32 offsetY);
    std::shared_ptr<Tile> createTile(sf::Uint32 x, sf::Uint32 y);

private:

    const size_t scale = 10;
    TileConfig config;
    
    std::shared_ptr<sf::Texture> texture;

};