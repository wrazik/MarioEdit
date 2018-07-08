#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>
#include "Tile.hpp"

class Cursor {

public:

    static void setWindow(std::shared_ptr<sf::RenderWindow>& window);

    Cursor();

    void draw();
    bool isOver(Tile& tile);

    void registerOver(Tile& tile);
    void unregisterOver(Tile& tile);
    bool isOverRegistered(Tile& tile);

private:

    static std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Sprite> sprite;

    std::vector<std::size_t> registeredOverTiles;

    void updatePosition();

};