#include <gtest/gtest.h>

#include <SFML/Graphics.hpp>
#include "classes/AnimationFrame.hpp"

#define EMPTY_CALLBACK [](){}

sf::Uint32 frameDuration = 1000;
AnimationFrame frame(0, 50, EMPTY_CALLBACK);

TEST(AnimationFrameTest, test_enters_now_on_begin) {
    EXPECT_TRUE(frame.entersNow(0, frameDuration));
}

TEST(AnimationFrameTest, test_enters_now_before_middle) {
    EXPECT_TRUE(frame.entersNow(499, frameDuration));
}

TEST(AnimationFrameTest, test_enters_now_on_middle) {
    EXPECT_FALSE(frame.entersNow(500, frameDuration));
}

TEST(AnimationFrameTest, test_enters_now_on_end) {
    EXPECT_FALSE(frame.entersNow(1000, frameDuration));
}