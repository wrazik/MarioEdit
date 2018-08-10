#include "Game.hpp"

#include <iostream>
#include "defines.hpp"
#include "Cursor.hpp"
#include "TileSet.hpp"
#include "Scale.hpp"
#include "TileRegistry.hpp"
#include "Animation/SpecialBlockBlinkingAnimation.hpp"

Game::Game() : tileSet("resources/tiles2.png") {
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(windowedWidth, windowedHeight), title, sf::Style::Default
    );

    grid = std::make_shared<Grid>(window->getSize());
    reinitializeWindow();
}

void Game::reinitializeWindow() {
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(100);
    window->setKeyRepeatEnabled(false);

    Scale::rescale(window->getSize());

    Cursor::reinitialize(window);
    Tile::setWindow(window);
    grid->rescale(window->getSize());
    snapTilesToGrid();
}

int Game::run() {
    createTiles();

    auto tiles = TileRegistry::getAll();
    
    SpecialBlockBlinkingAnimation blinkAnimation(tiles);
    blinkAnimation.run();

    while (window->isOpen()) {
        handleSystemEvents();
        handleTileEvents(tiles);

        window->clear(BG_LIGHT_COLOR);

        grid->draw(window);
        for (std::size_t i=0; i<tiles.size(); i++) {
            tiles[i]->draw(window);
        }

        cursor.draw();
        window->display();
    }
    return 0;
}

void Game::createTiles() {
    auto questionMark = tileSet.createTile(0, 5);
    questionMark->setEventHandler(Tile::MouseEnter, [](Tile* tile) {
        tile->highlight();
    });
    questionMark->setEventHandler(Tile::MouseLeave, [](Tile* tile) {
        tile->undoHighlight();
    });
    questionMark->setEventHandler(Tile::StartDrag, [](Tile* tile) {
        tile->change(0, 5);
        tile->startDrag();
    });
    questionMark->setEventHandler(Tile::Drag, [](Tile* tile) {
        tile->drag();
    });
    questionMark->setEventHandler(Tile::Drop, [](Tile* tile) {
        tile->drop();
    });

    questionMark->setGrid(grid);
    questionMark->snapToGrid(sf::Vector2u(2, 1));
}

void Game::handleTileEvents(const std::vector<std::shared_ptr<Tile>> &tiles) {
    for (size_t i=0; i < tiles.size(); i++) {
        auto tile = tiles[i];
        if (cursor.isOver(tile) && !cursor.isOverRegistered(tile)) {
            cursor.registerOver(tile);
            tile->handleEvent(Tile::MouseEnter);
        } else if (cursor.isOver(tile)) {
            tile->handleEvent(Tile::MouseOver);

            if (cursor.isClick() && !cursor.isDragRegistered(tile)) {
                cursor.registerDrag(tile);
                tile->handleEvent(Tile::StartDrag);
            } else if (!cursor.isClick() && cursor.isDragRegistered(tile)) {
                cursor.unregisterDrag(tile);
                tile->handleEvent(Tile::Drop);
            }
        } else if (!cursor.isOver(tile) && cursor.isOverRegistered(tile)) {
            if (cursor.isDragRegistered(tile)) {
                cursor.unregisterDrag(tile);
                tile->handleEvent(Tile::Drop);
            }
            cursor.unregisterOver(tile);
            tile->handleEvent(Tile::MouseLeave);
        } else {
            if (cursor.isDragRegistered(tile)) {
                cursor.unregisterDrag(tile);
                tile->handleEvent(Tile::Drop);
            }
        }
        tile->rescale(Scale::getScale());
    }
}

void Game::handleSystemEvents() {
    bool keyChanged = false;

    sf::Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                window->close();
            } break;
            case sf::Event::KeyPressed: {
                keyChanged = true;
                keyboard.press(event.key.code);
            } break;
            case sf::Event::KeyReleased: {
                keyChanged = true;
                keyboard.release(event.key.code);
            } break;
            case sf::Event::Resized: {
                width = event.size.width;
                height = event.size.height;
                windowedWidth = event.size.width;
                windowedHeight = event.size.height;

                if (event.size.height < minWindowHeight) {
                    window->setSize(sf::Vector2u(event.size.width, minWindowHeight));
                    height = minWindowHeight;
                    windowedHeight = minWindowHeight;
                }

                sf::Vector2u newSize(width, height);
                Scale::rescale(newSize);
                grid->rescale(newSize);
                snapTilesToGrid();
                window->setView(sf::View(sf::FloatRect(0, 0, width, height)));
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

    if (keyChanged) {
        handleKeyboardEvents();
    }
}

void Game::snapTilesToGrid() {
    auto tiles = TileRegistry::getAll();
    for (size_t i=0; i < tiles.size(); i++) {
        auto tile = tiles[i];
        tile->snapToGrid();
    }
}

void Game::handleKeyboardEvents() {
    if (keyboard.isPressed(sf::Keyboard::Escape) || keyboard.isPressed(sf::Keyboard::Q)) {
        window->close();
        return;
    }

    if (keyboard.isPressed(sf::Keyboard::F)) {
        isFullscreen = !isFullscreen;

        if (isFullscreen) {
            sf::VideoMode mode = findHighestResolutionMode();
            width = mode.width;
            height = mode.height;
            window->create(mode, title, isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        } else {
            width = windowedWidth;
            height = windowedHeight;

            sf::VideoMode mode(width, height);
            window->create(mode, title, isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
        }
        reinitializeWindow();
    }
}

sf::VideoMode Game::findHighestResolutionMode() {
    auto modes = sf::VideoMode::getFullscreenModes();
    auto maxHeightMode = modes[0];
    for (int i=0; i<modes.size(); i++) {
        if (modes[i].height > maxHeightMode.height) {
            maxHeightMode = modes[i];
        }
    }
    return maxHeightMode;
}
