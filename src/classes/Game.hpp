#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Keyboard.hpp"

class Game {

public:

    static std::size_t getWidth();
    static std::size_t getHeight();

    Game();

    int run();

private:

    static const std::size_t width = 1280;
    static const std::size_t height = 800;

    std::shared_ptr<sf::RenderWindow> window;
    
    Keyboard keyboard;

    void handleEvents();

};