#include <gtest/gtest.h>

#include "classes/Axis.hpp"

TEST(AxisTest, test_calculation_on_x_axis) {
    Axis axis;
    axis.rescale({200, 300});
    ASSERT_EQ(44, axis.percent(22, Direction::X));
}

TEST(AxisTest, test_calculation_on_y_axis) {
    Axis axis;
    axis.rescale({200, 300});

    ASSERT_EQ(66, axis.percent(22, Direction::Y));
}