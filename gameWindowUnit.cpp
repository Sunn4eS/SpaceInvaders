#include <SFML/Graphics.hpp>
#include "gameWindowUnit.h"


#include "RocketClass.h"
#include "CannonClass.h"

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

    //Rocket & Cannon initialize
    CannonClass cannon(windowSize.x / 2, 900);
    std::vector<RocketClass> rockets;


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
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    rockets.emplace_back(cannon.getBounds().left + cannon.getBounds().width / 2, cannon.getBounds().top);
                }

            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            cannon.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            cannon.moveRight();
        }

        cannon.update();
        for (auto& rocket : rockets) {
            rocket.update();
        }
        rockets.erase(std::remove_if(rockets.begin(), rockets.end(), [](RocketClass& rocket){
            return rocket.getBounds().top < 0;
        }), rockets.end());
        gameWindow.clear();
        gameWindow.draw(backgroundSprite);
        cannon.draw(gameWindow);
        for (auto& rocket : rockets) {
            rocket.draw(gameWindow);
        }
        gameWindow.display();

    }
}
