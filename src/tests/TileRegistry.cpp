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

TEST(TileRegistryTest, test_getall_no_tiles) {
    TileRegistry::clear();

    ASSERT_EQ(0, TileRegistry::getAll().size());
}

TEST(TileRegistryTest, test_getall_one_tile) {
    TileRegistry::clear();

    sf::Sprite sprite;
    auto tile = std::make_shared<Tile>(sprite);

    TileRegistry::registerTile(tile);
    ASSERT_EQ(1, TileRegistry::getAll().size());
}

TEST(TileRegistryTest, test_getall_two_tiles) {
    TileRegistry::clear();

    for (int i=0; i<2; i++) {
        sf::Sprite sprite;
        auto tile = std::make_shared<Tile>(sprite);
        TileRegistry::registerTile(tile);
    }

    ASSERT_EQ(2, TileRegistry::getAll().size());
}