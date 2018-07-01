#include "Keyboard.hpp"

void Keyboard::press(sf::Keyboard::Key key) {
    this->keys[key] = true;
}

void Keyboard::release(sf::Keyboard::Key key) {
    this->keys[key] = false;
}

bool Keyboard::isPressed(sf::Keyboard::Key key) {

    std::map<sf::Keyboard::Key, bool>::iterator it = this->keys.find(key);
    if(it != this->keys.end())
    {
       return it->second;
    }

    return false;
}