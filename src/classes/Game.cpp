#include "Game.hpp"

#include <iostream>
#include "defines.hpp"
#include "Cursor.hpp"
#include "TileSet.hpp"
#include "PositionCalc.hpp"

size_t Game::getWidth() {
    return Game::width;
}

size_t Game::getHeight() {
    return Game::height;
}

Game::Game() {
    this->window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(Game::width, Game::height), "Mario::Edit", sf::Style::Default
    );
    this->window->setVerticalSyncEnabled(true);
    this->window->setFramerateLimit(100);
    this->window->setKeyRepeatEnabled(false);

    PositionCalc::setWindowSize(this->window->getSize());
    Cursor::setWindow(this->window);
    Tile::setWindow(this->window);
}

int Game::run() {
    Cursor cursor;

    TileSet tileset("resources/tiles2.png");
    tileset.setTileSeparators(0, 0);
    Tile questionMark = tileset.createTile(0, 5);
    questionMark.setEventHandler(Tile::Event::MouseEnter, [](Tile* tile) {
        tile->highlight();
    });
    questionMark.setEventHandler(Tile::Event::MouseLeave, [](Tile* tile) {
        tile->undoHighlight();
    });

    PositionCalc posCalc;
    questionMark.setPosition(posCalc.percent(46, Axis::X), posCalc.percent(45, Axis::Y));

    while (this->window->isOpen()) {
        this->handleEvents();
        this->window->clear(BG_LIGHT_COLOR);

        if (cursor.isOver(questionMark) && !cursor.isOverRegistered(questionMark)) {
            cursor.registerOver(questionMark);
            questionMark.handleEvent(Tile::Event::MouseEnter);
        } else if (cursor.isOver(questionMark)) {
            questionMark.handleEvent(Tile::Event::MouseOver);
        } else if (!cursor.isOver(questionMark) && cursor.isOverRegistered(questionMark)) {
            cursor.unregisterOver(questionMark);
            questionMark.handleEvent(Tile::Event::MouseLeave);
        }

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
                this->window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            } break;
        }
    }

    if (this->keyboard.isPressed(sf::Keyboard::Escape)) {
        this->window->close();
    }
}