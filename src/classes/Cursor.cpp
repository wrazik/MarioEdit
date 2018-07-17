#include "Cursor.hpp"

#include <iostream>

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
    auto mousePosition = sf::Mouse::getPosition(*(Cursor::window));
    this->sprite->setPosition(mousePosition.x, mousePosition.y);
}

void Cursor::draw() {
    this->updatePosition();
    Cursor::window->draw(*(this->sprite));
}

bool Cursor::isOver(Tile &tile) {
    auto mousePosition = sf::Mouse::getPosition(*(Cursor::window));
    int posX = mousePosition.x;
    int posY = mousePosition.y;

    return posX >= tile.getPosition().x && posY >= tile.getPosition().y &&
           posX <= tile.getPosition().x+tile.getSize().x &&
           posY <= tile.getPosition().y+tile.getSize().y;
}

void Cursor::registerOver(Tile& tile) {
    if (!this->isOverRegistered(tile)) {
        this->registeredOverOnTiles.push_back(tile.getId());
    }
}

void Cursor::unregisterOver(Tile& tile) {
    if (this->isOverRegistered(tile)) {
        this->registeredOverOnTiles.erase(
                std::remove(this->registeredOverOnTiles.begin(), this->registeredOverOnTiles.end(), tile.getId()), this->registeredOverOnTiles.end()
        );
    }
}

bool Cursor::isOverRegistered(Tile& tile) {
    if (this->registeredOverOnTiles.empty()) {
        return false;
    }

    return std::find(this->registeredOverOnTiles.begin(), this->registeredOverOnTiles.end(), tile.getId()) != this->registeredOverOnTiles.end();
}

void Cursor::registerDrag(Tile &tile) {
    if (!this->isDragRegistered(tile)) {
        this->registeredDragOnTiles.push_back(tile.getId());
    }
}

void Cursor::unregisterDrag(Tile &tile) {
    if (this->isDragRegistered(tile)) {
        this->registeredDragOnTiles.erase(
                std::remove(this->registeredDragOnTiles.begin(), this->registeredDragOnTiles.end(), tile.getId()), this->registeredDragOnTiles.end()
        );
    }
}

bool Cursor::isDragRegistered(Tile &tile) {
    if (this->registeredDragOnTiles.empty()) {
        return false;
    }

    return std::find(this->registeredDragOnTiles.begin(), this->registeredDragOnTiles.end(), tile.getId()) != this->registeredDragOnTiles.end();
}

bool Cursor::isClick() {
    return this->clickFlag;
}

void Cursor::click(bool click) {
    this->clickFlag = click;
}

void Cursor::handleRegisteredDrags() {
    for (std::size_t i=0; i<this->registeredDragOnTiles.size(); i++) {
        this->registeredDragOnTiles[i];
    }
}
