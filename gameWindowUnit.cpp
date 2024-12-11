//
// Created by User on 11.12.2024.
//
#include <SFML/Graphics.hpp>
#include "gameWindowUnit.h"

#include <iostream>

#define GAME_WINDOW_WIDTH 1920
#define GAME_WINDOW_HEIGHT 1080


void game() {
    sf::RenderWindow gameWindow(sf::VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT), "Construction of the game");
    sf::Vector2u windowSize = gameWindow.getSize();
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images\\BackGroundImage.png")) {
        std::cerr << "Failed to load background texture" << std::endl;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    //Pause Button



    //Main Cycle
    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
            if (event.type == sf::Event::Resized) {
                windowSize.x = GAME_WINDOW_WIDTH;
                windowSize.y = GAME_WINDOW_HEIGHT;
                gameWindow.setSize(windowSize);
            }

        }
        gameWindow.clear();
        gameWindow.draw(backgroundSprite);
        gameWindow.display();

    }
}
