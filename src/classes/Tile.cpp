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
    position = {(float)posX, (float)posY};
    sprite.setPosition(position);
}

sf::Vector2f Tile::getPosition() {
    return sprite.getPosition();
}

sf::Vector2i Tile::getSize() {
    return sf::Vector2i(
            sprite.getTextureRect().width*sprite.getScale().x,
            sprite.getTextureRect().height*sprite.getScale().y
    );
}

void Tile::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}

void Tile::handleEvent(Tile::Event event) {
    switch (event) {
        case Tile::Event::MouseOver: {
            if (mouseOverCallback != nullptr) {
                mouseOverCallback(this);
            }
        } break;
        case Tile::Event::MouseEnter: {
            if (mouseEnterCallback != nullptr) {
                mouseEnterCallback(this);
            }
        } break;
        case Tile::Event::MouseLeave: {
            if (mouseLeaveCallback != nullptr) {
                mouseLeaveCallback(this);
            }
        } break;
        case Tile::Event::StartDrag: {
            if (startDragCallback != nullptr) {
                startDragCallback(this);
            }
        } break;
        case Tile::Event::Drag: {
            if (dragCallback != nullptr) {
                dragCallback(this);
            }
        } break;
        case Tile::Event::Drop: {
            if (dropCallback != nullptr) {
                dropCallback(this);
            }
        } break;
    }
}

void Tile::setEventHandler(Tile::Event event, std::function<void(Tile* tile)> callback) {
    switch (event) {
        case Tile::Event::MouseOver: {
            mouseOverCallback = callback;
        } break;
        case Tile::Event::MouseEnter: {
            mouseEnterCallback = callback;
        } break;
        case Tile::Event::MouseLeave: {
            mouseLeaveCallback = callback;
        } break;
        case Tile::Event::StartDrag: {
            startDragCallback = callback;
        } break;
        case Tile::Event::Drag: {
            dragCallback = callback;
        } break;
        case Tile::Event::Drop: {
            dropCallback = callback;
        } break;
    }
}

void Tile::highlight() {
    scalePromotion = 1.2f;

    rescaleCenter();
    correctCorners();
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
    return position.x == 0;
}

bool Tile::isOnRightEdge() {
    return position.x+getSize().x == window->getSize().x;
}

bool Tile::isOnTopEdge() {
    return position.y == 0;
}

bool Tile::isOnBottomEdge() {
    return position.y+getSize().y == window->getSize().y;
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
    auto newSpriteScaleX = scaleX*scalePromotion;
    auto newSpriteScaleY = scaleY*scalePromotion;

    sprite.setScale(newSpriteScaleX, newSpriteScaleY);

    position.x = 0;
    position.y = 0;
    sprite.setPosition(position);
}

void Tile::rescaleToBottomLeftCorner() {
    auto newSpriteScaleX = scaleX*scalePromotion;
    auto newSpriteScaleY = scaleY*scalePromotion;

    sprite.setScale(newSpriteScaleX, newSpriteScaleY);

    position.x = 0;
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void Tile::rescaleToBottomRightCorner() {
    auto newSpriteScaleX = scaleX*scalePromotion;
    auto newSpriteScaleY = scaleY*scalePromotion;

    sprite.setScale(newSpriteScaleX, newSpriteScaleY);

    position.x = window->getSize().x-getSize().x;
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void Tile::rescaleToTopRightCorner() {
    auto newSpriteScaleX = scaleX*scalePromotion;
    auto newSpriteScaleY = scaleY*scalePromotion;

    sprite.setScale(newSpriteScaleX, newSpriteScaleY);

    position.x = window->getSize().x-getSize().x;
    position.y = 0;
    sprite.setPosition(position);
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
    position.x = window->getSize().x-getSize().x;
    sprite.setPosition(position);
}

void Tile::rescaleToTopEdge() {
    rescaleCenter();
    position.y = 0;
    sprite.setPosition(position);
}

void Tile::rescaleToBottomEdge() {
    rescaleCenter();
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void Tile::correctCorners() {
    auto width = getSize().x;
    auto height = getSize().y;

    auto posX = sprite.getPosition().x;
    if (posX < 0) {
        posX = 0;
    }

    auto posY = sprite.getPosition().y;
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

    position.x = posX;
    position.y = posY;
    sprite.setPosition(position);
}

void Tile::rescale(float scaleX, float scaleY) {
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    sprite.setScale(scaleX*scalePromotion, scaleY*scalePromotion);
}

void Tile::startDrag() {
    sprite.setColor(sf::Color(255, 255, 255, 180));

    auto cursorPosition = Cursor::getCurrentPosition();
    dragOffset.x = cursorPosition.x - sprite.getPosition().x;
    dragOffset.y = cursorPosition.y - sprite.getPosition().y;
}

void Tile::drag() {
    auto cursorPosition = Cursor::getCurrentPosition();
    cursorPosition -= dragOffset;
    sprite.setPosition(cursorPosition.x, cursorPosition.y);

    correctCorners();
}

void Tile::drop() {
    sprite.setColor(sf::Color(255, 255, 255, 255));
    dragOffset = {0, 0};
}
