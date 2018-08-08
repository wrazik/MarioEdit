#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

class AnimationFrame {

public:

    AnimationFrame(std::size_t leftBound, std::size_t rightBound, std::function<void()> callback);

    bool entersNow(sf::Int32 animationPointInTime, sf::Int32 duration);
    void enter();

private:

    std::size_t leftBound = 0;
    std::size_t rightBound = 100;
    std::function<void()> callback;

};