#include "TileRegistry.hpp"

std::vector<std::shared_ptr<Tile>> TileRegistry::allTiles;

void TileRegistry::clear() {
    TileRegistry::allTiles.clear();
}

void TileRegistry::registerTile(std::shared_ptr<Tile> tile) {
    TileRegistry::allTiles.push_back(tile);
}

std::vector<std::shared_ptr<Tile>> TileRegistry::getAll() {
    return TileRegistry::allTiles;
}
