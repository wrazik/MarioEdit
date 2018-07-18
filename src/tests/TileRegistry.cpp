#include <gtest/gtest.h>

#include "classes/TileRegistry.hpp"
#include "classes/Tile.hpp"
#include "classes/Exception/TileNotFoundException.hpp"

TEST(TileRegistryTest, test_tile_not_found) {
    TileRegistry::clear();
    ASSERT_THROW(TileRegistry::getTile(1500), TileNotFoundException);
}

TEST(TileRegistryTest, test_tile_found) {
    TileRegistry::clear();
    sf::Sprite sprite;
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(sprite);

    TileRegistry::registerTile(tile);
    ASSERT_NO_THROW(TileRegistry::getTile(tile->getId()));
}