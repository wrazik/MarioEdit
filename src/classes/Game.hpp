#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Keyboard.hpp"
#include "Axis.hpp"

class Game {

public:

    Game();

    int run();

private:

    const std::string title = "Mario::Edit";
    std::size_t width = 1280;
    std::size_t height = 800;
    bool fullscreen = false;

    std::shared_ptr<sf::RenderWindow> window;

    Axis axis;
    Keyboard keyboard;

    void handleEvents();

};