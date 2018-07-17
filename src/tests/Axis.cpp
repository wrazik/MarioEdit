#include <gtest/gtest.h>

#include "classes/Axis.hpp"

TEST(AxisTest, test_calculation_on_x_axis) {
    sf::Vector2u newSize(200, 300);
    Axis::rescale(newSize);

    Axis calc;
    ASSERT_EQ(44, calc.percent(22, Direction::X));
}

TEST(AxisTest, test_calculation_on_y_axis) {
    sf::Vector2u newSize(200, 300);
    Axis::rescale(newSize);

    Axis calc;
    ASSERT_EQ(66, calc.percent(22, Direction::Y));
}