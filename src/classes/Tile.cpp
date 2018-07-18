#include "Tile.hpp"

#include <iostream>
#include "classes/TileRegistry.hpp"
#include "classes/Cursor.hpp"

std::size_t Tile::nextId = 1;

std::shared_ptr<sf::RenderWindow> Tile::window;

void Tile::setWindow(std::shared_ptr<sf::RenderWindow> &window) {
    Tile::window = window;
}

Tile::Tile(sf::Sprite sprite) {
    this->id = nextId;
    Tile::nextId++;

    this->sprite = sprite;
}

std::size_t Tile::getId() {
    return this->id;
}

void Tile::setPosition(int posX, int posY) {
    this->sprite.setPosition(posX, posY);
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
    this->scalePromotion = 1.4f;

    this->highlightReturn = this->sprite.getPosition();
    this->rescaleCenter();
    this->correctCorners();
}

void Tile::undoHighlight() {
    this->scalePromotion = 1.0f;
    this->scalePromotionBeforeDrag = 1.0f;

    this->rescaleCenter();
    this->sprite.setPosition(this->highlightReturn);
}

void Tile::rescaleCenter() {
    auto newSpriteScale = sprite.getScale()*scalePromotion;

    auto newWidth = sprite.getTextureRect().width * newSpriteScale.x;
    auto newHeight = sprite.getTextureRect().height * newSpriteScale.y;

    auto diffWidth = (newWidth - getSize().x) / 2;
    auto diffHeight = (newHeight - getSize().y) / 2;

    sprite.setScale(newSpriteScale);
    sprite.setPosition(
        sprite.getPosition().x - diffWidth,
        sprite.getPosition().y - diffHeight
    );
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

    this->sprite.setPosition(posX, posY);
}

void Tile::rescale(float scaleX, float scaleY) {
    this->sprite.setScale(scaleX*scalePromotion, scaleY*scalePromotion);
}

void Tile::startDrag() {
    scalePromotionBeforeDrag = scalePromotion;
    scalePromotion = 1.0f;
    sprite.setColor(sf::Color(255, 255, 255, 180));
    this->drag();
}

void Tile::drag() {
    auto cursorPosition = Cursor::getCurrentPosition();
    cursorPosition -= this->getSize()/2;
    sprite.setPosition(cursorPosition.x, cursorPosition.y);
}

void Tile::drop() {
    sprite.setColor(sf::Color(255, 255, 255, 255));
    scalePromotion = scalePromotionBeforeDrag;
}
