#include <gtest/gtest.h>

#include "classes/Grid.hpp"

sf::Vector2u windowSize(1280, 800);
Grid grid(windowSize);


TEST(GridTest, test_tile_0_0_point_on_top_left_corner) {
    sf::Vector2f point(0, 0);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_top_right_corner) {
    sf::Vector2f point(65, 0);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_bottom_right_corner) {
    sf::Vector2f point(65, 65);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_bottom_left_corner) {
    sf::Vector2f point(0, 65);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_left_edge) {
    sf::Vector2f point(0, 10);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_right_edge) {
    sf::Vector2f point(65, 10);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_top_edge) {
    sf::Vector2f point(10, 0);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_bottom_edge) {
    sf::Vector2f point(10, 65);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_0_0_point_on_inside) {
    sf::Vector2f point(10, 10);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(0, gridPoint.x);
    ASSERT_FLOAT_EQ(0, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_top_left_corner) {
    sf::Vector2f point(2*66, 66);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_top_right_corner) {
    sf::Vector2f point(2*66+65, 66);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_bottom_right_corner) {
    sf::Vector2f point(2*66+65, 66+65);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_bottom_left_corner) {
    sf::Vector2f point(2*66, 66+65);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_left_edge) {
    sf::Vector2f point(2*66, 66+10);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_right_edge) {
    sf::Vector2f point(2*66+65, 66+10);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_top_edge) {
    sf::Vector2f point(2*66+10, 66);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_bottom_edge) {
    sf::Vector2f point(2*66+10, 66+65);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}

TEST(GridTest, test_tile_2_1_point_on_inside) {
    sf::Vector2f point(2*66+10, 66+10);
    sf::Vector2f gridPoint = grid.getPointOnGrid(point);

    ASSERT_FLOAT_EQ(2*66, gridPoint.x);
    ASSERT_FLOAT_EQ(66, gridPoint.y);
}