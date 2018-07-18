#pragma once

#include <vector>
#include <map>
#include "Tile.hpp"

class TileRegistry {

public:

    static void clear();
    static void registerTile(std::shared_ptr<Tile> tile);
    static std::shared_ptr<Tile> getTile(std::size_t tileId);

private:

    static std::map<std::size_t, std::shared_ptr<Tile>> registeredTiles;
    static std::vector<std::shared_ptr<Tile>> allTiles;

};
