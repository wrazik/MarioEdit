#pragma once

#include <vector>
#include <map>
#include "Tile.hpp"

class TileRegistry {

public:

    static void clear();
    static void registerTile(std::shared_ptr<Tile> tile);
    static std::vector<std::shared_ptr<Tile>> getAll();

private:

    static std::vector<std::shared_ptr<Tile>> allTiles;

};
