#include "TileRegistry.hpp"

std::vector<std::shared_ptr<Tile>> TileRegistry::allTiles;

void TileRegistry::clear() {
    allTiles.clear();
}

void TileRegistry::registerTile(std::shared_ptr<Tile> tile) {
    allTiles.push_back(tile);
}

std::vector<std::shared_ptr<Tile>> TileRegistry::getAll() {
    return allTiles;
}
