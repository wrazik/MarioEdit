#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>
#include "Tile.hpp"

class Cursor {

public:

    static void reinitialize(std::shared_ptr<sf::RenderWindow> &window);

    Cursor();

    void draw();
    bool isOver(Tile& tile);

    bool isClick();
    void click(bool click);

    void registerOver(Tile& tile);
    void unregisterOver(Tile& tile);
    bool isOverRegistered(Tile& tile);

    void registerDrag(Tile& tile);
    void unregisterDrag(Tile& tile);
    bool isDragRegistered(Tile& tile);

    void handleRegisteredDrags();

private:

    static std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Sprite> sprite;

    std::vector<std::size_t> registeredOverOnTiles;
    std::vector<std::size_t> registeredDragOnTiles;

    bool clickFlag;

    void updatePosition();

};