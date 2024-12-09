
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "newPlayerWindowUnit.h"

#define CHOOSE_PLAYER_WINDOW_WIDTH 800
#define CHOOSE_PLAYER_WINDOW_HEIGHT 500
#define CHOOSE_PLAYER_BUTTON_WIDTH 180
#define CHOOSE_PLAYER_BUTTON_HEIGHT 90
#define CHOOSE_PLAYER_SHIFT_BUTTON 80


bool isMouseOverButtonC(const sf::RectangleShape& button, const sf::Vector2i& mousePos) {
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
void choosePlayer () {

    sf::RenderWindow chooseWindow(sf::VideoMode(CHOOSE_PLAYER_WINDOW_WIDTH, CHOOSE_PLAYER_WINDOW_HEIGHT), "Choose Player");
    sf::Vector2u chooseWindowSize = chooseWindow.getSize();
    int currWindowWidth = chooseWindowSize.x;
    int currWindowHeight = chooseWindowSize.y;

    //BackGround
    sf::Texture backgroundChoosePlayerTexture;
    if (!backgroundChoosePlayerTexture.loadFromFile("images\\PlayerBackgroundImage.png")) {
        std::cerr << "Failed to load background texture" << std::endl;
    }
    sf::Sprite backgroundChoosePlayerSprite(backgroundChoosePlayerTexture);
    sf::Vector2u textureSize = backgroundChoosePlayerTexture.getSize();
    float scaleX = static_cast<float>(chooseWindowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(chooseWindowSize.y) / textureSize.y;
    backgroundChoosePlayerSprite.setScale(scaleX, scaleY);

    //NewPlayer Button
    sf::RectangleShape newPlayerButton(sf::Vector2f(CHOOSE_PLAYER_BUTTON_WIDTH, CHOOSE_PLAYER_BUTTON_HEIGHT));
    sf::Texture newPlayerButtonTexture;
    if (!newPlayerButtonTexture.loadFromFile("images\\NewPlayerButton.png")) {
        std::cerr << "Failed to load scoreButton texture" << std::endl;
    }
    newPlayerButton.setPosition((currWindowWidth - newPlayerButton.getSize().x) / 2 - CHOOSE_PLAYER_SHIFT_BUTTON * 3.1f, currWindowHeight / 2 + CHOOSE_PLAYER_SHIFT_BUTTON * 1.5);
    newPlayerButton.setTexture(&newPlayerButtonTexture, true);


    while (chooseWindow.isOpen()) {
        sf::Event event;
        while (chooseWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                chooseWindow.close();
            }
            if (event.type == sf::Event::Resized) {
                chooseWindowSize.x = CHOOSE_PLAYER_WINDOW_WIDTH;
                chooseWindowSize.y = CHOOSE_PLAYER_WINDOW_HEIGHT;
                chooseWindow.setSize(chooseWindowSize);
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(chooseWindow);
                if (isMouseOverButtonC(newPlayerButton, mousePos)) {
                    newPlayerWin();
                }
            }
        }
        chooseWindow.clear();
        chooseWindow.draw(backgroundChoosePlayerSprite);
        chooseWindow.draw(newPlayerButton);
        chooseWindow.display();
    }


}
