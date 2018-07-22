#include "TileSet.hpp"
#include "Scale.hpp"
#include "TileRegistry.hpp"

TileSet::TileSet(std::string filepath)
{
    texture = std::make_shared<sf::Texture>();
    texture->loadFromFile(filepath);
}

void TileSet::setTileSeparators(std::size_t separatorX, std::size_t separatorY)
{
    this->separatorX = separatorX;
    this->separatorY = separatorY;
}

void TileSet::setTileOffset(std::size_t offsetX, std::size_t offsetY)
{
    this->offsetX = offsetX;
    this->offsetY = offsetY;
}

std::shared_ptr<Tile> TileSet::createTile(std::size_t x, std::size_t y)
{
    sf::Sprite sprite;
    sprite.setTexture(*(texture));
    sprite.setScale(Scale::getScale(), Scale::getScale());

    sf::IntRect textureRect;
    textureRect.width = tileWidth;
    textureRect.height = tileHeight;

    textureRect.top = (y * (tileHeight+separatorY)) + offsetY;
    textureRect.left = (x * (tileHeight+separatorX)) + offsetX;
    sprite.setTextureRect(textureRect);

    auto tile = std::make_shared<Tile>(sprite);
    TileRegistry::registerTile(tile);

    return tile;
}