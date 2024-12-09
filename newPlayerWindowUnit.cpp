//
// Created by User on 09.12.2024.
//
#include <SFML/Graphics.hpp>
#include "newPlayerWindowUnit.h"
#include <iostream>

#define NEW_PLAYER_WINDOW_WIDTH 650
#define NEW_PLAYER_WINDOW_HEIGHT 400


void newPlayerWin() {
    sf::RenderWindow newPlayerWindow(sf::VideoMode (NEW_PLAYER_WINDOW_WIDTH, NEW_PLAYER_WINDOW_HEIGHT ), "New Player");

    //background image
    sf::Vector2u newPlayerWindowSize = newPlayerWindow.getSize();
    sf::Texture backgroundNewPlayerTexture;
    if (!backgroundNewPlayerTexture.loadFromFile("images\\AddNewPlayerBackground.png")) {
        std::cerr << "Failed to load background texture" << std::endl;
    }
    sf::Sprite backgroundNewPlayerSprite(backgroundNewPlayerTexture);
    sf::Vector2u textureSize = backgroundNewPlayerTexture.getSize();
    float scaleX = static_cast<float>(newPlayerWindowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(newPlayerWindowSize.y) / textureSize.y;
    backgroundNewPlayerSprite.setScale(scaleX, scaleY);

    //main cycle
    while (newPlayerWindow.isOpen()) {
        sf::Event event;
        while (newPlayerWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                newPlayerWindow.close();
            }
            if (event.type == sf::Event::Resized) {
                sf::Vector2u windowSize;
                windowSize.x = NEW_PLAYER_WINDOW_WIDTH;
                windowSize.y = NEW_PLAYER_WINDOW_HEIGHT;
                newPlayerWindow.setSize(windowSize);
            }
        }



        newPlayerWindow.clear();
        newPlayerWindow.draw(backgroundNewPlayerSprite);
        newPlayerWindow.display();

    }
}
