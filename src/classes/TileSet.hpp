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

    void setTileSeparators(std::size_t separatorX, std::size_t separatorY);
    void setTileOffset(std::size_t offsetX, std::size_t offsetY);
    std::shared_ptr<Tile> createTile(std::size_t x, std::size_t y);

private:

    const size_t scale = 10;
    TileConfig config;
    
    std::shared_ptr<sf::Texture> texture;

};