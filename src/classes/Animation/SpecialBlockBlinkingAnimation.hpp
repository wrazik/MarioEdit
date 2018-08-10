#pragma once

#include "classes/Animation.hpp"
#include "classes/Tile.hpp"

class SpecialBlockBlinkingAnimation : public Animation {

public:

    SpecialBlockBlinkingAnimation(std::vector<std::shared_ptr<Tile>> tiles);

};