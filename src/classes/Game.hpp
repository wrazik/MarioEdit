#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Keyboard.hpp"
#include "Axis.hpp"

class Game {

public:

    static std::size_t getWidth();
    static std::size_t getHeight();

    Game();

    int run();

private:

    static const std::string title;
    static std::size_t width;
    static std::size_t height;
    bool fullscreen = false;

    std::shared_ptr<sf::RenderWindow> window;

    Axis axis;
    Keyboard keyboard;

    void handleEvents();

};