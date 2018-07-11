#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"

class TileSet
{

public:

    TileSet(std::string filepath);

    void setTileSeparators(std::size_t separatorX, std::size_t separatorY);
    void setTileOffset(std::size_t offsetX, std::size_t offsetY);
    Tile createTile(std::size_t x, std::size_t y);

private:

    const size_t scale = 10;
    const std::size_t tileWidth = 16;
    const std::size_t tileHeight = 16;
    
    std::shared_ptr<sf::Texture> texture;
    std::size_t separatorX = 0;
    std::size_t separatorY = 0;
    std::size_t offsetX = 0;
    std::size_t offsetY = 0;

};