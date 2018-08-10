#include "Animation.hpp"

#include <thread>

void Animation::run() {
    sf::Clock clock;
    sf::Int32 startMilliseconds = clock.getElapsedTime().asMilliseconds();

    std::thread interval([=]() {
        while (true) {
            sf::Int32 currentMilliseconds = clock.getElapsedTime().asMilliseconds();
            sf::Int32 animationPointInTime = (currentMilliseconds-startMilliseconds) % duration;

            for (std::size_t i=0; i<frames.size(); i++) {
                if (frames.at(i)->entersNow(animationPointInTime, duration)) {
                    frames.at(i)->enter();
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
    });
    interval.detach();
}

void Animation::addFrame(std::shared_ptr<AnimationFrame> frame) {
    frames.push_back(frame);
}