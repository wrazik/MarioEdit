#include "Tile.hpp"

#include <iostream>
#include "classes/TileRegistry.hpp"
#include "classes/Cursor.hpp"

std::shared_ptr<sf::RenderWindow> Tile::window;

void Tile::setWindow(std::shared_ptr<sf::RenderWindow> &window) {
    Tile::window = window;
}

Tile::Tile(sf::Sprite sprite, TileConfig config) {
    this->sprite = sprite;
    this->config = config;
}

void Tile::change(sf::Uint32 x, sf::Uint32 y) {
    sf::IntRect textureRect;
    textureRect.width = config.tileWidth;
    textureRect.height = config.tileHeight;

    textureRect.top = (y * (config.tileHeight+config.separatorY)) + config.offsetY;
    textureRect.left = (x * (config.tileWidth+config.separatorX)) + config.offsetX;
    sprite.setTextureRect(textureRect);
}

void Tile::setPosition(sf::Vector2f position) {
    this->position = position;
    sprite.setPosition(position);
}

sf::Vector2f Tile::getPosition() {
    return sprite.getPosition();
}

void Tile::setGrid(std::shared_ptr<Grid> grid) {
    this->grid = grid;
}

void Tile::snapToGrid() {
    setPosition(grid->pointOnGridToPosition(gridPosition));
}

void Tile::snapToGrid(sf::Vector2u gridPosition) {
    this->gridPosition = gridPosition;
    setPosition(grid->pointOnGridToPosition(gridPosition));
}

sf::Vector2i Tile::getSize() {
    return sf::Vector2i(
        sprite.getTextureRect().width * sprite.getScale().x,
        sprite.getTextureRect().height * sprite.getScale().y
    );
}

void Tile::draw(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(sprite);
}

void Tile::handleEvent(Tile::Event event) {
    switch (event) {
        case Tile::Event::MouseOver: {
            isMouseOverFlag = true;
            if (mouseOverCallback != nullptr) {
                mouseOverCallback(this);
            }
        } break;
        case Tile::Event::MouseEnter: {
            isMouseOverFlag = true;
            if (mouseEnterCallback != nullptr) {
                mouseEnterCallback(this);
            }
        } break;
        case Tile::Event::MouseLeave: {
            isMouseOverFlag = false;
            if (mouseLeaveCallback != nullptr) {
                mouseLeaveCallback(this);
            }
        } break;
        case Tile::Event::StartDrag: {
            isDraggingFlag = true;
            if (startDragCallback != nullptr) {
                startDragCallback(this);
            }
        } break;
        case Tile::Event::Drag: {
            isDraggingFlag = true;
            if (dragCallback != nullptr) {
                dragCallback(this);
            }
        } break;
        case Tile::Event::Drop: {
            isDraggingFlag = false;
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

bool Tile::isMouseOver() {
    return isMouseOverFlag;
}

bool Tile::isDragging() {
    return isDraggingFlag;
}

void Tile::highlight() {
    scalePromotion = 1.5f;

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
    snapToGrid();
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
    sprite.setScale(scale*scalePromotion);

    position.x = 0;
    position.y = 0;
    sprite.setPosition(position);
}

void Tile::rescaleToBottomLeftCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = 0;
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void Tile::rescaleToBottomRightCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = window->getSize().x-getSize().x;
    position.y = window->getSize().y-getSize().y;
    sprite.setPosition(position);
}

void Tile::rescaleToTopRightCorner() {
    sprite.setScale(scale*scalePromotion);

    position.x = window->getSize().x-getSize().x;
    position.y = 0;
    sprite.setPosition(position);
}

void Tile::rescaleCenter() {
    auto newSpriteScale = scale*scalePromotion;

    auto newWidth = sprite.getTextureRect().width * newSpriteScale.x;
    auto newHeight = sprite.getTextureRect().height * newSpriteScale.y;

    auto diffWidth = (newWidth - getSize().x) / 2;
    auto diffHeight = (newHeight - getSize().y) / 2;

    sprite.setScale(newSpriteScale.x, newSpriteScale.y);

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

    position = sf::Vector2f(posX, posY);
    sprite.setPosition(position);
}

void Tile::rescale(float scale) {
    this->scale = sf::Vector2f(scale, scale);
    sprite.setScale(this->scale*scalePromotion);
}

void Tile::startDrag() {
    sprite.setColor(sf::Color(255, 255, 255, 180));

    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHightlightPosition(cursorPosition);
    
    dragOffset = sf::Vector2f(cursorPosition) - sprite.getPosition();

    grid->hightlightOn();
}

void Tile::drag() {
    auto cursorPosition = Cursor::getCurrentPosition();
    grid->setHightlightPosition(cursorPosition);

    cursorPosition -= dragOffset;
    sprite.setPosition(sf::Vector2f(cursorPosition));

    correctCorners();
}

void Tile::drop() {
    sprite.setColor(sf::Color(255, 255, 255, 255));
    dragOffset = {0, 0};

    snapToGrid(grid->getHighlightPlace());

    sf::Vector2f positionOnGrid = grid->getHighlightPosition();
    if (isMouseOverFlag) {
        sf::Vector2f tileSize(getSize());
        positionOnGrid -= (tileSize-(tileSize/scalePromotion))/2.0f;
    }

    setPosition(positionOnGrid);
    grid->hightlightOff();

    if (isMouseOverFlag) {
        correctCorners();
    }
}

sf::Vector2f Tile::getCenterPoint() {
    sf::Vector2f retval = position;
    retval.x += getSize().x/2;
    retval.y += getSize().y/2;
    return retval;
}
