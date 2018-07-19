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
    TileSet tileset("resources/tiles2.png");
    auto questionMark = tileset.createTile(0, 5);
    questionMark->setEventHandler(Tile::Event::MouseEnter, [](Tile* tile) {
        tile->highlight();
    });
    questionMark->setEventHandler(Tile::Event::MouseLeave, [](Tile* tile) {
        tile->undoHighlight();
    });
    questionMark->setEventHandler(Tile::Event::StartDrag, [](Tile* tile) {
        tile->startDrag();
    });
    questionMark->setEventHandler(Tile::Event::Drag, [](Tile* tile) {
        tile->drag();
    });
    questionMark->setEventHandler(Tile::Event::Drop, [](Tile* tile) {
        tile->drop();
    });

    questionMark->setPosition(0, 0);

    while (this->window->isOpen()) {
        this->handleEvents();

        if (cursor.isOver(questionMark) && !cursor.isOverRegistered(questionMark)) {
            cursor.registerOver(questionMark);
            questionMark->handleEvent(Tile::Event::MouseEnter);
        } else if (cursor.isOver(questionMark)) {
            questionMark->handleEvent(Tile::Event::MouseOver);

            if (cursor.isClick() && !cursor.isDragRegistered(questionMark)) {
                cursor.registerDrag(questionMark);
                questionMark->handleEvent(Tile::Event::StartDrag);
            } else if (!cursor.isClick() && cursor.isDragRegistered(questionMark)) {
                cursor.unregisterDrag(questionMark);
                questionMark->handleEvent(Tile::Event::Drop);
            }
        } else if (!cursor.isOver(questionMark) && cursor.isOverRegistered(questionMark)) {
            cursor.unregisterOver(questionMark);
            questionMark->handleEvent(Tile::Event::MouseLeave);
        } else {
            if (cursor.isDragRegistered(questionMark)) {
                cursor.unregisterDrag(questionMark);
                questionMark->handleEvent(Tile::Event::Drop);
            }
        }
        questionMark->rescale(Axis::getScale(), Axis::getScale());

        this->window->clear(BG_LIGHT_COLOR);

        questionMark->draw(this->window);
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
            case sf::Event::MouseButtonPressed: {
                cursor.click(true);
            } break;
            case sf::Event::MouseButtonReleased: {
                cursor.click(false);
            } break;
            case sf::Event::MouseMoved: {
                cursor.handleRegisteredDrags();
            } break;
        }
    }

    if (this->keyboard.isPressed(sf::Keyboard::Escape) || this->keyboard.isPressed(sf::Keyboard::Q)) {
        this->window->close();
        return;
    }

    if (this->keyboard.isPressed(sf::Keyboard::F) || this->keyboard.isPressed(sf::Keyboard::G)) {
        this->fullscreen = this->keyboard.isPressed(sf::Keyboard::F);
        this->window->create(sf::VideoMode(this->width, this->height), this->title, this->fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        this->axis.rescale(this->window->getSize());
        Cursor::reinitialize(this->window);
    }
}