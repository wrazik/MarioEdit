#include "TileRegistry.hpp"

#include "Exception/TileNotFoundException.hpp"

std::map<std::size_t, std::shared_ptr<Tile>> TileRegistry::registeredTiles;
std::vector<std::shared_ptr<Tile>> TileRegistry::allTiles;

void TileRegistry::clear() {
    TileRegistry::registeredTiles.clear();
    TileRegistry::allTiles.clear();
}

void TileRegistry::registerTile(std::shared_ptr<Tile> tile) {
    TileRegistry::registeredTiles[tile->getId()] = tile;
    TileRegistry::allTiles.push_back(tile);
}

std::shared_ptr<Tile> TileRegistry::getTile(std::size_t tileId) {
    auto search = TileRegistry::registeredTiles.find(tileId);
    if(search != TileRegistry::registeredTiles.end()) {
        return search->second;
    } else {
        TileNotFoundException e;
        throw e;
    }
}

std::vector<std::shared_ptr<Tile>> TileRegistry::getAll() {
    return TileRegistry::allTiles;
}
