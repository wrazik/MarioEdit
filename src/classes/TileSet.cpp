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
    config.separatorX = separatorX;
    config.separatorY = separatorY;
}

void TileSet::setTileOffset(std::size_t offsetX, std::size_t offsetY)
{
    config.offsetX = offsetX;
    config.offsetY = offsetY;
}

std::shared_ptr<Tile> TileSet::createTile(std::size_t x, std::size_t y)
{
    sf::Sprite sprite;
    sprite.setTexture(*(texture));
    sprite.setScale(Scale::getScale(), Scale::getScale());

    auto tile = std::make_shared<Tile>(sprite, config);
    tile->change(x, y);
    TileRegistry::registerTile(tile);

    return tile;
}