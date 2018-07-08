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
    };

    static void setWindow(std::shared_ptr<sf::RenderWindow>& window);

    Tile(sf::Sprite sprite);

    std::size_t getId();

    void setPosition(int posX, int posY);
    sf::Vector2f getPosition();
    sf::Vector2i getSize();

    void draw(std::shared_ptr<sf::RenderWindow> window);
    void handleEvent(Tile::Event event);
    void setEventHandler(Tile::Event event, std::function<void(Tile* tile)> callback);

    void highlight();
    void undoHighlight();

private:

    static std::size_t nextId;
    static std::shared_ptr<sf::RenderWindow> window;

    std::size_t id;
    sf::Vector2f highlightReturn;

    sf::Sprite sprite;
    std::function<void(Tile* tile)> mouseOverCallback = nullptr;
    std::function<void(Tile* tile)> mouseEnterCallback = nullptr;
    std::function<void(Tile* tile)> mouseLeaveCallback = nullptr;

    void rescaleCenter(const sf::Vector2<float> &newSpriteScale);
    void correctCorners();
};