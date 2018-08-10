#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

class Grid
{

public:

    Grid(sf::Vector2u windowSize);
    void rescale(sf::Vector2u windowSize);
    sf::Vector2f getPointOnGrid(sf::Vector2f pointOnScreen);
    sf::Vector2f pointOnGridToPosition(sf::Vector2u pointOnGrid);
    sf::Vector2f getHighlightPosition();
    sf::Vector2u getHighlightPlace();
    void draw(std::shared_ptr<sf::RenderWindow> window);

    void hightlightOn();
    void hightlightOff();
    void setHightlightPosition(sf::Vector2f cursorPosition);

private:

    sf::Vector2u windowSize;
    sf::Uint32 rows = 12;
    float distance;
    
    sf::Uint32 lineThickness;
    sf::Uint32 lineThicknessDivider = 400;
    
    sf::Color lineColor;
    
    bool hightlight = false;
    sf::Vector2f highlightPosition;

    void drawHorizontalLine(sf::Uint32 number, std::shared_ptr<sf::RenderWindow> window);
    void drawVerticalLine(sf::Uint32 number, std::shared_ptr<sf::RenderWindow> window);
    void drawHightlight(std::shared_ptr<sf::RenderWindow> window);
};
