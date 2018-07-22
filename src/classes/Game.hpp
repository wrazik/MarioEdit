#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Keyboard.hpp"
#include "Scale.hpp"
#include "Cursor.hpp"
#include "TileSet.hpp"

class Game {

public:

    Game();

    int run();

private:

    const std::string title = "Mario::Edit";
    std::size_t width = 1280;
    std::size_t height = 960;
    std::size_t windowedWidth = 1280;
    std::size_t windowedHeight = 960;
    bool isFullscreen = false;

    std::shared_ptr<sf::RenderWindow> window;

    Scale axis;
    Cursor cursor;
    Keyboard keyboard;
    TileSet tileSet;


    void handleSystemEvents();
    void handleTileEvents(const std::vector<std::shared_ptr<Tile>> &tiles);
    void createTiles();

    void handleKeyboardEvents();

    void reinitializeWindow();
    sf::VideoMode findHighestResolutionMode();

    void rescaleTilesPosition();
};