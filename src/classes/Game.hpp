#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Keyboard.hpp"
#include "Axis.hpp"
#include "Cursor.hpp"

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
    bool fullscreen = false;

    std::shared_ptr<sf::RenderWindow> window;

    Axis axis;
    Cursor cursor;
    Keyboard keyboard;

    void handleEvents();

    void reinitializeWindow();

    sf::VideoMode findHighestResolutionMode();
};