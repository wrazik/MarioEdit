#include "TileSet.hpp"

TileSet::TileSet(std::string filepath)
{
    this->texture = std::make_shared<sf::Texture>();
    this->texture->loadFromFile(filepath);
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

Tile TileSet::createTile(std::size_t x, std::size_t y)
{
    sf::Sprite sprite;
    sprite.setTexture(*(this->texture));
    sprite.setScale(this->scale, this->scale);

    sf::IntRect textureRect;
    textureRect.width = this->tileWidth;
    textureRect.height = this->tileHeight;

    textureRect.top = (y * (this->tileHeight+separatorY)) + this->offsetY;
    textureRect.left = (x * (this->tileHeight+separatorX)) + this->offsetX;
    sprite.setTextureRect(textureRect);

    return Tile(sprite);
}