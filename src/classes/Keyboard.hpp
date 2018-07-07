#pragma once

#include <map>
#include <SFML/Graphics.hpp>

class Keyboard {

public:

    void press(sf::Keyboard::Key key);
    void release(sf::Keyboard::Key key);

    bool isPressed(sf::Keyboard::Key key);

private:

    std::map<sf::Keyboard::Key, bool> keys;

};