#include "Cursor.hpp"

#include "TileRegistry.hpp"

std::shared_ptr<sf::RenderWindow> Cursor::window;

void Cursor::reinitialize(std::shared_ptr<sf::RenderWindow> &window) {
    Cursor::window = window;
    Cursor::window->setMouseCursorVisible(false);
}

Cursor::Cursor() {
    this->texture = std::make_shared<sf::Texture>();
    this->texture->loadFromFile("resources/cursor.png");

    sprite = std::make_shared<sf::Sprite>(*(texture));

    float scale = 0.15;
    sprite->scale(scale, scale);
}

void Cursor::updatePosition() {
    auto mousePosition = Cursor::getCurrentPosition();
    sprite->setPosition(mousePosition.x, mousePosition.y);
}

sf::Vector2f Cursor::getCurrentPosition() {
    return sf::Vector2f(sf::Mouse::getPosition(*(window)));
}

void Cursor::draw() {
    updatePosition();
    Cursor::window->draw(*sprite);
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
    if (!isOverRegistered(tile)) {
        registeredOverOnTiles.push_back(tile);
    }
}

void Cursor::unregisterOver(std::shared_ptr<Tile> tile) {
    if (isOverRegistered(tile)) {
        registeredOverOnTiles.erase(
                std::remove(registeredOverOnTiles.begin(), registeredOverOnTiles.end(), tile), registeredOverOnTiles.end()
        );
    }
}

bool Cursor::isOverRegistered(std::shared_ptr<Tile> tile) {
    if (registeredOverOnTiles.empty()) {
        return false;
    }

    return std::find(registeredOverOnTiles.begin(), registeredOverOnTiles.end(), tile) != registeredOverOnTiles.end();
}

void Cursor::registerDrag(std::shared_ptr<Tile> tile) {
    if (!isDragRegistered(tile)) {
        registeredDragOnTiles.push_back(tile);
    }
}

void Cursor::unregisterDrag(std::shared_ptr<Tile> tile) {
    if (isDragRegistered(tile)) {
        registeredDragOnTiles.erase(
                std::remove(registeredDragOnTiles.begin(), registeredDragOnTiles.end(), tile), registeredDragOnTiles.end()
        );
    }
}

bool Cursor::isDragRegistered(std::shared_ptr<Tile> tile) {
    if (registeredDragOnTiles.empty()) {
        return false;
    }

    return std::find(this->registeredDragOnTiles.begin(), this->registeredDragOnTiles.end(), tile) != this->registeredDragOnTiles.end();
}

bool Cursor::isClick() {
    return clickFlag;
}

void Cursor::click(bool click) {
    clickFlag = click;
}

void Cursor::handleRegisteredDrags() {
    for (std::size_t i=0; i<registeredDragOnTiles.size(); i++) {
        registeredDragOnTiles[i]->handleEvent(Tile::Event::Drag);
    }
}
