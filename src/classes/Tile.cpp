#include "Tile.hpp"

#include <iostream>
#include "classes/TileRegistry.hpp"
#include "classes/Cursor.hpp"

std::shared_ptr<sf::RenderWindow> Tile::window;

void Tile::setWindow(std::shared_ptr<sf::RenderWindow> &window) {
    Tile::window = window;
}

Tile::Tile(sf::Sprite sprite) {
    this->sprite = sprite;
}

void Tile::setPosition(int posX, int posY) {
    this->position = {(float)posX, (float)posY};
    this->sprite.setPosition(this->position);
}

sf::Vector2f Tile::getPosition() {
    return this->sprite.getPosition();
}

sf::Vector2i Tile::getSize() {
    return sf::Vector2i(
            this->sprite.getTextureRect().width*this->sprite.getScale().x,
            this->sprite.getTextureRect().height*this->sprite.getScale().y
    );
}

void Tile::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(this->sprite);
}

void Tile::handleEvent(Tile::Event event) {
    switch (event) {
        case Tile::Event::MouseOver: {
            if (this->mouseOverCallback != nullptr) {
                this->mouseOverCallback(this);
            }
        } break;
        case Tile::Event::MouseEnter: {
            if (this->mouseEnterCallback != nullptr) {
                this->mouseEnterCallback(this);
            }
        } break;
        case Tile::Event::MouseLeave: {
            if (this->mouseLeaveCallback != nullptr) {
                this->mouseLeaveCallback(this);
            }
        } break;
        case Tile::Event::StartDrag: {
            if (this->startDragCallback != nullptr) {
                this->startDragCallback(this);
            }
        } break;
        case Tile::Event::Drag: {
            if (this->dragCallback != nullptr) {
                this->dragCallback(this);
            }
        } break;
        case Tile::Event::Drop: {
            if (this->dropCallback != nullptr) {
                this->dropCallback(this);
            }
        } break;
    }
}

void Tile::setEventHandler(Tile::Event event, std::function<void(Tile* tile)> callback) {
    switch (event) {
        case Tile::Event::MouseOver: {
            this->mouseOverCallback = callback;
        } break;
        case Tile::Event::MouseEnter: {
            this->mouseEnterCallback = callback;
        } break;
        case Tile::Event::MouseLeave: {
            this->mouseLeaveCallback = callback;
        } break;
        case Tile::Event::StartDrag: {
            this->startDragCallback = callback;
        } break;
        case Tile::Event::Drag: {
            this->dragCallback = callback;
        } break;
        case Tile::Event::Drop: {
            this->dropCallback = callback;
        } break;
    }
}

void Tile::highlight() {
    this->scalePromotion = 1.2f;

    this->rescaleCenter();
    this->correctCorners();
}

void Tile::undoHighlight() {
    scalePromotion = 1.0f;

    if (isOnTopLeftCorner()) {
        rescaleToTopLeftCorner();
    } else if (isOnBottomLeftCorner()) {
        rescaleToBottomLeftCorner();
    } else if (isOnBottomRightCorner()) {
        rescaleToBottomRightCorner();
    } else if (isOnTopRightCorner()) {
        rescaleToTopRightCorner();
    } else if (isOnLeftEdge()) {
        rescaleToLeftEdge();
    } else if (isOnRightEdge()) {
        rescaleToRightEdge();
    } else if (isOnTopEdge()) {
        rescaleToTopEdge();
    } else if (isOnBottomEdge()) {
        rescaleToBottomEdge();
    } else {
        rescaleCenter();
    }
}

bool Tile::isOnLeftEdge() {
    return this->position.x == 0;
}

bool Tile::isOnRightEdge() {
    return this->position.x+this->getSize().x == this->window->getSize().x;
}

bool Tile::isOnTopEdge() {
    return this->position.y == 0;
}

bool Tile::isOnBottomEdge() {
    return this->position.y+this->getSize().y == this->window->getSize().y;
}

bool Tile::isOnTopRightCorner() {
    return isOnTopEdge() && isOnRightEdge();
}

bool Tile::isOnBottomRightCorner() {
    return isOnBottomEdge() && isOnRightEdge();
}

bool Tile::isOnBottomLeftCorner() {
    return isOnBottomEdge() && isOnLeftEdge();
}

bool Tile::isOnTopLeftCorner() {
    return isOnTopEdge() && isOnLeftEdge();
}

void Tile::rescaleToTopLeftCorner() {
    auto newSpriteScaleX = this->scaleX*scalePromotion;
    auto newSpriteScaleY = this->scaleY*scalePromotion;

    sprite.setScale(newSpriteScaleX, newSpriteScaleY);

    this->position.x = 0;
    this->position.y = 0;
    sprite.setPosition(this->position);
}

void Tile::rescaleToBottomLeftCorner() {
    auto newSpriteScaleX = this->scaleX*scalePromotion;
    auto newSpriteScaleY = this->scaleY*scalePromotion;

    sprite.setScale(newSpriteScaleX, newSpriteScaleY);

    this->position.x = 0;
    this->position.y = this->window->getSize().y-this->getSize().y;
    sprite.setPosition(this->position);
}

void Tile::rescaleToBottomRightCorner() {
    auto newSpriteScaleX = this->scaleX*scalePromotion;
    auto newSpriteScaleY = this->scaleY*scalePromotion;

    sprite.setScale(newSpriteScaleX, newSpriteScaleY);

    this->position.x = this->window->getSize().x-this->getSize().x;
    this->position.y = this->window->getSize().y-this->getSize().y;
    sprite.setPosition(this->position);
}

void Tile::rescaleToTopRightCorner() {
    auto newSpriteScaleX = this->scaleX*scalePromotion;
    auto newSpriteScaleY = this->scaleY*scalePromotion;

    sprite.setScale(newSpriteScaleX, newSpriteScaleY);

    this->position.x = this->window->getSize().x-this->getSize().x;
    this->position.y = 0;
    sprite.setPosition(this->position);
}

void Tile::rescaleCenter() {
    auto newSpriteScaleX = scaleX*scalePromotion;
    auto newSpriteScaleY = scaleY*scalePromotion;

    auto newWidth = sprite.getTextureRect().width * newSpriteScaleX;
    auto newHeight = sprite.getTextureRect().height * newSpriteScaleY;

    auto diffWidth = (newWidth - getSize().x) / 2;
    auto diffHeight = (newHeight - getSize().y) / 2;

    sprite.setScale(newSpriteScaleX, newSpriteScaleY);

    position.x = sprite.getPosition().x - diffWidth;
    position.y = sprite.getPosition().y - diffHeight;
    sprite.setPosition(position);
}

void Tile::rescaleToLeftEdge() {
    rescaleCenter();
    position.x = 0;
    sprite.setPosition(position);
}

void Tile::rescaleToRightEdge() {
    rescaleCenter();
    position.x = this->window->getSize().x-this->getSize().x;
    sprite.setPosition(position);
}

void Tile::rescaleToTopEdge() {
    rescaleCenter();
    position.y = 0;
    sprite.setPosition(position);
}

void Tile::rescaleToBottomEdge() {
    rescaleCenter();
    position.y = this->window->getSize().y-this->getSize().y;
    sprite.setPosition(position);
}

void Tile::correctCorners() {
    auto width = this->getSize().x;
    auto height = this->getSize().y;

    auto posX = this->sprite.getPosition().x;
    if (posX < 0) {
        posX = 0;
    }

    auto posY = this->sprite.getPosition().y;
    if (posY < 0) {
        posY = 0;
    }

    auto windowWidth = Tile::window->getSize().x;
    if (posX+width > windowWidth) {
        posX = windowWidth-width;
    }

    auto windowHeight = Tile::window->getSize().y;
    if (posY+height > windowHeight) {
        posY = windowHeight-height;
    }

    this->position.x = posX;
    this->position.y = posY;
    this->sprite.setPosition(this->position);
}

void Tile::rescale(float scaleX, float scaleY) {
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->sprite.setScale(scaleX*scalePromotion, scaleY*scalePromotion);
}

void Tile::startDrag() {
    sprite.setColor(sf::Color(255, 255, 255, 180));

    auto cursorPosition = Cursor::getCurrentPosition();
    dragOffset.x = cursorPosition.x - sprite.getPosition().x;
    dragOffset.y = cursorPosition.y - sprite.getPosition().y;
    this->drag();
}

void Tile::drag() {
    auto cursorPosition = Cursor::getCurrentPosition();
    cursorPosition -= this->dragOffset;
    sprite.setPosition(cursorPosition.x, cursorPosition.y);

    this->correctCorners();
}

void Tile::drop() {
    sprite.setColor(sf::Color(255, 255, 255, 255));
    dragOffset = {0, 0};
}
