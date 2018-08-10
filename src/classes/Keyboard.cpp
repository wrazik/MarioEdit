#include "Keyboard.hpp"

void Keyboard::press(sf::Keyboard::Key key) {
    keys[key] = true;
}

void Keyboard::release(sf::Keyboard::Key key) {
    keys[key] = false;
}

bool Keyboard::isPressed(sf::Keyboard::Key key) {
    std::map<sf::Keyboard::Key, bool>::iterator it = keys.find(key);
    if (it != keys.end()) {
       return it->second;
    }
    return false;
}