#include "SpecialBlockBlinkingAnimation.hpp"

SpecialBlockBlinkingAnimation::SpecialBlockBlinkingAnimation(std::vector<std::shared_ptr<Tile>> tiles) {
    duration = 1000;

    addFrame(std::make_shared<AnimationFrame>(0, 70, [=]() {
        for (std::size_t i=0; i<tiles.size(); i++) {
            if (!tiles.at(i)->isDragging()) {
                tiles.at(i)->change(0, 5);
            }
        }
    }));

    addFrame(std::make_shared<AnimationFrame>(70, 80, [=]() {
        for (std::size_t i=0; i<tiles.size(); i++) {
            if (!tiles.at(i)->isDragging()) {
                tiles.at(i)->change(1, 5);
            }
        }
    }));

    addFrame(std::make_shared<AnimationFrame>(80, 90, [=]() {
        for (std::size_t i=0; i<tiles.size(); i++) {
            if (!tiles.at(i)->isDragging()) {
                tiles.at(i)->change(2, 5);
            }
        }
    }));

    addFrame(std::make_shared<AnimationFrame>(90, 100, [=]() {
        for (std::size_t i=0; i<tiles.size(); i++) {
            if (!tiles.at(i)->isDragging()) {
                tiles.at(i)->change(1, 5);
            }
        }
    }));
}