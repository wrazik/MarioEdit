#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

class AnimationFrame {

public:

    AnimationFrame(sf::Uint32 leftBound, sf::Uint32 rightBound, std::function<void()> callback);

    bool entersNow(sf::Int32 animationPointInTime, sf::Int32 duration);
    void enter();

private:

    sf::Uint32 leftBound = 0;
    sf::Uint32 rightBound = 100;
    std::function<void()> callback;

};