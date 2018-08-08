#pragma once

#include <SFML/Graphics.hpp>
#include "AnimationFrame.hpp"

class Animation {

public:

    void run();

protected:

    sf::Uint32 sleepTime = 10;
    sf::Uint32 duration = 1000;
    std::vector<std::shared_ptr<AnimationFrame>> frames;

    void addFrame(std::shared_ptr<AnimationFrame> frame);

};