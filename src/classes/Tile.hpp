#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

class Tile
{

public:

    enum Event {
        MouseOver,
        MouseEnter,
        MouseLeave,
        StartDrag,
        Drag,
        Drop,
    };

    static void setWindow(std::shared_ptr<sf::RenderWindow>& window);

    Tile(sf::Sprite sprite);

    void setPosition(int posX, int posY);
    sf::Vector2f getPosition();

    sf::Vector2i getSize();

    void rescale(float scaleX, float scaleY);
    void draw(std::shared_ptr<sf::RenderWindow> window);
    void handleEvent(Tile::Event event);
    void setEventHandler(Tile::Event event, std::function<void(Tile* tile)> callback);

    void highlight();
    void undoHighlight();
    void startDrag();
    void drag();
    void drop();

private:

    static std::shared_ptr<sf::RenderWindow> window;

    sf::Vector2i dragOffset = {0, 0};
    sf::Vector2f position;

    float scaleX = 1.0f;
    float scaleY = 1.0f;
    float scalePromotion = 1.0f;

    sf::Sprite sprite;
    std::function<void(Tile* tile)> mouseOverCallback = nullptr;
    std::function<void(Tile* tile)> mouseEnterCallback = nullptr;
    std::function<void(Tile* tile)> mouseLeaveCallback = nullptr;
    std::function<void(Tile* tile)> startDragCallback = nullptr;
    std::function<void(Tile* tile)> dragCallback = nullptr;
    std::function<void(Tile* tile)> dropCallback = nullptr;

    void rescaleCenter();
    void correctCorners();

    bool isOnLeftEdge();
    bool isOnRightEdge();
    bool isOnTopEdge();
    bool isOnBottomEdge();

    bool isOnTopLeftCorner();
    bool isOnBottomLeftCorner();
    bool isOnBottomRightCorner();
    bool isOnTopRightCorner();

    void rescaleToTopLeftCorner();
    void rescaleToBottomLeftCorner();
    void rescaleToBottomRightCorner();
    void rescaleToTopRightCorner();

    void rescaleToLeftEdge();
    void rescaleToRightEdge();
    void rescaleToTopEdge();
    void rescaleToBottomEdge();
};