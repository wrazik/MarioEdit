#include "Cursor.hpp"

std::shared_ptr<sf::RenderWindow> Cursor::window;

void Cursor::setWindow(std::shared_ptr<sf::RenderWindow> &window) {
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
        this->registeredOverTiles.push_back(tile.getId());
    }
}

void Cursor::unregisterOver(Tile& tile) {
    if (this->isOverRegistered(tile)) {
        this->registeredOverTiles.erase(
                std::remove(this->registeredOverTiles.begin(), this->registeredOverTiles.end(), tile.getId()), this->registeredOverTiles.end()
        );
    }
}

bool Cursor::isOverRegistered(Tile& tile) {
    if (this->registeredOverTiles.empty()) {
        return false;
    }

    return std::find(this->registeredOverTiles.begin(), this->registeredOverTiles.end(), tile.getId()) != this->registeredOverTiles.end();
}
