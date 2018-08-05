#include "Grid.hpp"

#include <iostream>

Grid::Grid(sf::Vector2u windowSize) : lineColor(74, 119, 203, 255) {
    this->rescale(windowSize);
}

void Grid::rescale(sf::Vector2u windowSize) {
    this->windowSize = windowSize;

    size = windowSize.y / sizeDivider;
    distance = windowSize.y / rows;
}

sf::Vector2f Grid::getPointOnGrid(sf::Vector2f pointOnScreen) {
    sf::Vector2f retval = {0, 0};
    retval.x = ((int)(pointOnScreen.x/distance))*distance;
    retval.y = ((int)(pointOnScreen.y/distance))*distance;
    return retval;
}

void Grid::draw(std::shared_ptr<sf::RenderWindow> window) {
    for (int i=0; i<rows+1; i++) {
        drawHorizontalLine(i, window);
    }

    std::size_t columnsCount = windowSize.x / distance;
    for (int i=1; i<columnsCount+1; i++) {
        drawVerticalLine(i, window);
    }

    if (hightlight) {
        drawHightlight(window);
    }
}

void Grid::drawHorizontalLine(std::size_t number, std::shared_ptr<sf::RenderWindow> window) {
    std::size_t posY = number*distance;

    sf::RectangleShape line;
    line.setPosition(sf::Vector2f(0, posY-size/2));
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(windowSize.x, size));

    window->draw(line);
}

void Grid::drawVerticalLine(std::size_t number, std::shared_ptr<sf::RenderWindow> window) {
    std::size_t posX = number*distance;

    sf::RectangleShape line;
    line.setPosition(sf::Vector2f(posX-size/2, 0));
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(size, windowSize.y));

    window->draw(line);
}

void Grid::drawHightlight(std::shared_ptr<sf::RenderWindow> window) {
    sf::RectangleShape line;
    line.setPosition(highlightPosition);
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(distance, distance));

    window->draw(line);
}

void Grid::hightlightOn() {
    hightlight = true;
}

void Grid::hightlightOff() {
    hightlight = false;
}

void Grid::setHightlightPosition(sf::Vector2f cursorPosition) {
    highlightPosition = getPointOnGrid(cursorPosition);
}