#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>
#include "Tile.hpp"

class Cursor {

public:

    static void reinitialize(std::shared_ptr<sf::RenderWindow> &window);
    static sf::Vector2f getCurrentPosition();

    Cursor();


    void draw();
    bool isOver(std::shared_ptr<Tile> tile);

    bool isClick();
    void click(bool click);

    void registerOver(std::shared_ptr<Tile> tile);
    void unregisterOver(std::shared_ptr<Tile> tile);
    bool isOverRegistered(std::shared_ptr<Tile> tile);

    void registerDrag(std::shared_ptr<Tile> tile);
    void unregisterDrag(std::shared_ptr<Tile> tile);
    bool isDragRegistered(std::shared_ptr<Tile> tile);

    void handleRegisteredDrags();

private:

    static std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Sprite> sprite;

    std::vector<std::shared_ptr<Tile>> registeredOverOnTiles;
    std::vector<std::shared_ptr<Tile>> registeredDragOnTiles;

    bool clickFlag;

    void updatePosition();
};