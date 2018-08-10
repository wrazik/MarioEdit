#include "AnimationFrame.hpp"

AnimationFrame::AnimationFrame(sf::Uint32 leftBound, sf::Uint32 rightBound, std::function<void()> callback) {
    this->leftBound = leftBound;
    this->rightBound = rightBound;
    this->callback = callback;
}

bool AnimationFrame::entersNow(sf::Int32 animationPointInTime, sf::Int32 duration) {
    sf::Int32 currentPercent = (float)(animationPointInTime)/(float)(duration)*100;
    return currentPercent >= leftBound && currentPercent < rightBound;
}

void AnimationFrame::enter() {
    callback();
}