#include "Game.hpp"

#include <iostream>
#include "defines.hpp"
#include "Cursor.hpp"
#include "TileSet.hpp"
#include "Axis.hpp"

Game::Game() {
    this->window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(this->width, this->height), this->title, sf::Style::Default
    );
    this->window->setVerticalSyncEnabled(true);
    this->window->setFramerateLimit(100);
    this->window->setKeyRepeatEnabled(false);

    this->axis.rescale(this->window->getSize());
    Cursor::reinitialize(this->window);
    Tile::setWindow(this->window);
}

int Game::run() {
    Cursor cursor;

    TileSet tileset("resources/tiles2.png");
    Tile questionMark = tileset.createTile(0, 5);
    questionMark.setEventHandler(Tile::Event::MouseEnter, [](Tile* tile) {
        tile->highlight();
    });
    questionMark.setEventHandler(Tile::Event::MouseLeave, [](Tile* tile) {
        tile->undoHighlight();
    });

    questionMark.setPosition(0, 0);

    while (this->window->isOpen()) {
        questionMark.rescale(Axis::getScale(), Axis::getScale());

        this->handleEvents();

        if (cursor.isOver(questionMark) && !cursor.isOverRegistered(questionMark)) {
            cursor.registerOver(questionMark);
            questionMark.handleEvent(Tile::Event::MouseEnter);
        } else if (cursor.isOver(questionMark)) {
            questionMark.handleEvent(Tile::Event::MouseOver);
        } else if (!cursor.isOver(questionMark) && cursor.isOverRegistered(questionMark)) {
            cursor.unregisterOver(questionMark);
            questionMark.handleEvent(Tile::Event::MouseLeave);
        }

        this->window->clear(BG_LIGHT_COLOR);

        questionMark.draw(this->window);
        cursor.draw();

        this->window->display();
    }
    return 0;
}

void Game::handleEvents() {
    sf::Event event;
    while (this->window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                this->window->close();
            } break;
            case sf::Event::KeyPressed: {
                this->keyboard.press(event.key.code);
            } break;
            case sf::Event::KeyReleased: {
                this->keyboard.release(event.key.code);
            } break;
            case sf::Event::Resized: {
                this->width = event.size.width;
                this->height = event.size.height;

                sf::Vector2u newSize(this->width, this->height);
                this->axis.rescale(newSize);
                this->window->setView(sf::View(sf::FloatRect(0, 0, this->width, this->height)));
            } break;
        }
    }

    if (this->keyboard.isPressed(sf::Keyboard::Escape) || this->keyboard.isPressed(sf::Keyboard::Q)) {
        this->window->close();
    }

    if (this->keyboard.isPressed(sf::Keyboard::LAlt) && this->keyboard.isPressed(sf::Keyboard::Enter)) {
        this->fullscreen = !this->fullscreen;
        this->window->create(sf::VideoMode(this->width, this->height), this->title, this->fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        this->axis.rescale(this->window->getSize());
        Cursor::reinitialize(this->window);
    }
}