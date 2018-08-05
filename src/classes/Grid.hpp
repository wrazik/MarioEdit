#pragma once

#include <SFML/Graphics.hpp>

class Grid
{

public:

    Grid(sf::Vector2u windowSize);
    void rescale(sf::Vector2u windowSize);
    sf::Vector2f getPointOnGrid(sf::Vector2f pointOnScreen);
    sf::Vector2f getHighlightPosition();
    void draw(std::shared_ptr<sf::RenderWindow> window);

    void hightlightOn();
    void hightlightOff();
    void setHightlightPosition(sf::Vector2f cursorPosition);

private:

    sf::Vector2u windowSize;
    std::size_t rows = 12;
    float distance;
    std::size_t size;
    std::size_t sizeDivider = 400;
    sf::Color lineColor;
    bool hightlight = false;
    sf::Vector2f highlightPosition;

    void drawHorizontalLine(std::size_t number, std::shared_ptr<sf::RenderWindow> window);
    void drawVerticalLine(std::size_t number, std::shared_ptr<sf::RenderWindow> window);
    void drawHightlight(std::shared_ptr<sf::RenderWindow> window);
};