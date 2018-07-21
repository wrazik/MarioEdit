#include "Cursor.hpp"
#include "TileRegistry.hpp"

#include <iostream>
#include <classes/Exception/TileNotFoundException.hpp>

std::shared_ptr<sf::RenderWindow> Cursor::window;

void Cursor::reinitialize(std::shared_ptr<sf::RenderWindow> &window) {
    Cursor::window = window;
    Cursor::window->setMouseCursorVisible(false);
}

Cursor::Cursor() {
    this->texture = std::make_shared<sf::Texture>();
    this->texture->loadFromFile("resources/cursor.png");

    this->sprite = std::make_shared<sf::Sprite>(*(this->texture));

    float scale = 0.15;
    this->sprite->scale(scale, scale);
}

void Cursor::updatePosition() {
    auto mousePosition = Cursor::getCurrentPosition();
    this->sprite->setPosition(mousePosition.x, mousePosition.y);
}

sf::Vector2i Cursor::getCurrentPosition() {
    return sf::Mouse::getPosition(*(window));
}

void Cursor::draw() {
    this->updatePosition();
    Cursor::window->draw(*(this->sprite));
}

bool Cursor::isOver(std::shared_ptr<Tile> tile) {
    auto mousePosition = sf::Mouse::getPosition(*(Cursor::window));
    int posX = mousePosition.x;
    int posY = mousePosition.y;

    return posX >= tile->getPosition().x && posY >= tile->getPosition().y &&
           posX <= tile->getPosition().x+tile->getSize().x &&
           posY <= tile->getPosition().y+tile->getSize().y;
}

void Cursor::registerOver(std::shared_ptr<Tile> tile) {
    if (!this->isOverRegistered(tile)) {
        this->registeredOverOnTiles.push_back(tile);
    }
}

void Cursor::unregisterOver(std::shared_ptr<Tile> tile) {
    if (this->isOverRegistered(tile)) {
        this->registeredOverOnTiles.erase(
                std::remove(this->registeredOverOnTiles.begin(), this->registeredOverOnTiles.end(), tile), this->registeredOverOnTiles.end()
        );
    }
}

bool Cursor::isOverRegistered(std::shared_ptr<Tile> tile) {
    if (this->registeredOverOnTiles.empty()) {
        return false;
    }

    return std::find(this->registeredOverOnTiles.begin(), this->registeredOverOnTiles.end(), tile) != this->registeredOverOnTiles.end();
}

void Cursor::registerDrag(std::shared_ptr<Tile> tile) {
    if (!this->isDragRegistered(tile)) {
        this->registeredDragOnTiles.push_back(tile);
    }
}

void Cursor::unregisterDrag(std::shared_ptr<Tile> tile) {
    if (this->isDragRegistered(tile)) {
        this->registeredDragOnTiles.erase(
                std::remove(this->registeredDragOnTiles.begin(), this->registeredDragOnTiles.end(), tile), this->registeredDragOnTiles.end()
        );
    }
}

bool Cursor::isDragRegistered(std::shared_ptr<Tile> tile) {
    if (this->registeredDragOnTiles.empty()) {
        return false;
    }

    return std::find(this->registeredDragOnTiles.begin(), this->registeredDragOnTiles.end(), tile) != this->registeredDragOnTiles.end();
}

bool Cursor::isClick() {
    return this->clickFlag;
}

void Cursor::click(bool click) {
    this->clickFlag = click;
}

void Cursor::handleRegisteredDrags() {
    for (std::size_t i=0; i<this->registeredDragOnTiles.size(); i++) {
        this->registeredDragOnTiles[i]->handleEvent(Tile::Event::Drag);
    }
}
