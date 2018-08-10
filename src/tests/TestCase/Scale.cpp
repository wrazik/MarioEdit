#include <gtest/gtest.h>

#include <SFML/Graphics.hpp>
#include "classes/Scale.hpp"

TEST(ScaleTest, test_default_scale) {
    Scale::reset();

    EXPECT_FLOAT_EQ(Scale::getScale(), 1.0f);
    EXPECT_FLOAT_EQ(Scale::getScaleRatio(), 1.0f);
}

TEST(ScaleTest, test_handle_first_window_size) {
    Scale::reset();
    Scale::rescale(sf::Vector2u(1280, 800));

    EXPECT_FLOAT_EQ(Scale::getScale(), 4.1666665);
    EXPECT_FLOAT_EQ(Scale::getScaleRatio(), 1.0f);
}

TEST(ScaleTest, test_handle_two_window_sizes) {
    Scale::reset();
    Scale::rescale(sf::Vector2u(1280, 800));
    Scale::rescale(sf::Vector2u(800, 600));

    EXPECT_FLOAT_EQ(Scale::getScale(), 3.125);
    EXPECT_FLOAT_EQ(Scale::getScaleRatio(), 0.75f);
}

TEST(ScaleTest, test_handle_width_rescalling) {
    Scale::reset();
    Scale::rescale(sf::Vector2u(1280, 800));
    Scale::rescale(sf::Vector2u(800, 800));

    EXPECT_FLOAT_EQ(Scale::getScale(), 4.1666665);
    EXPECT_FLOAT_EQ(Scale::getScaleRatio(), 1.0f);
}

TEST(ScaleTest, test_handle_height_rescalling) {
    Scale::reset();
    Scale::rescale(sf::Vector2u(1280, 800));
    Scale::rescale(sf::Vector2u(1280, 600));

    EXPECT_FLOAT_EQ(Scale::getScale(), 3.125);
    EXPECT_FLOAT_EQ(Scale::getScaleRatio(), 0.75);
}

TEST(ScaleTest, test_handle_rescalling_to_same_dimensions) {
    Scale::reset();
    Scale::rescale(sf::Vector2u(1280, 800));
    Scale::rescale(sf::Vector2u(1280, 800));

    EXPECT_FLOAT_EQ(Scale::getScale(), 4.1666665);
    EXPECT_FLOAT_EQ(Scale::getScaleRatio(), 1.0f);
}