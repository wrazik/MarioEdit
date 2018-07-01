#include <gtest/gtest.h>

#include "classes/PositionCalc.hpp"

TEST(PositionCalcTest, test_calculation_on_x_axis) {
    PositionCalc::setWindowSize({200, 300});

    PositionCalc calc;
    ASSERT_EQ(44, calc.percent(22, Axis::X));
}

TEST(PositionCalcTest, test_calculation_on_y_axis) {
    PositionCalc::setWindowSize({200, 300});

    PositionCalc calc;
    ASSERT_EQ(66, calc.percent(22, Axis::Y));
}