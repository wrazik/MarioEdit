#include "Game.hpp"

#include <iostream>
#include "defines.hpp"
#include "Cursor.hpp"
#include "TileSet.hpp"
#include "Axis.hpp"

const std::string Game::title = "Mario::Edit";

std::size_t Game::width = 1280;

std::size_t Game::height = 800;

size_t Game::getWidth() {
    return Game::width;
}

size_t Game::getHeight() {
    return Game::height;
}

Game::Game() {
    this->window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(Game::width, Game::height), Game::title, sf::Style::Default
    );
    this->window->setVerticalSyncEnabled(true);
    this->window->setFramerateLimit(100);
    this->window->setKeyRepeatEnabled(false);

    this->axis.rescale(this->window->getSize());
    Cursor::setWindow(this->window);
    Tile::setWindow(this->window);
}

int Game::run() {
    Cursor cursor;

    TileSet tileset("resources/tiles2.png");
    Tile questionMark = tileset.createTile(0, 5);
    questionMark.setEventHandler(Tile::Event::MouseOver, [](Tile* tile) {
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
                Game::width = event.size.width;
                Game::height = event.size.height;

                this->axis.rescale({event.size.width, event.size.height});
                this->window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            } break;
        }
    }

    if (this->keyboard.isPressed(sf::Keyboard::Escape) || this->keyboard.isPressed(sf::Keyboard::Q)) {
        this->window->close();
    }

    if (this->keyboard.isPressed(sf::Keyboard::LAlt) && this->keyboard.isPressed(sf::Keyboard::Enter)) {
        this->fullscreen = !this->fullscreen;
        this->window->create(sf::VideoMode(Game::width, Game::height), Game::title, this->fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        this->axis.rescale(this->window->getSize());
    }
}