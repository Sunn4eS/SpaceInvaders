
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "choosePlayerWindow.h"
#include "DropBox.h"
#include "fileModule.h"
#include "newPlayerWindowUnit.h"

#define CHOOSE_PLAYER_WINDOW_WIDTH 800
#define CHOOSE_PLAYER_WINDOW_HEIGHT 500
#define CHOOSE_PLAYER_BUTTON_WIDTH 180
#define CHOOSE_PLAYER_BUTTON_HEIGHT 90
#define CHOOSE_PLAYER_SHIFT_BUTTON 80

PlayerLinkedList::player_t* currentPlayer = nullptr;



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

    //Delete PLayer
    sf::RectangleShape deletePlayerButton(sf::Vector2f(CHOOSE_PLAYER_BUTTON_WIDTH, CHOOSE_PLAYER_BUTTON_HEIGHT));
    sf::Texture deletePlayerButtonTexture;
    if (!deletePlayerButtonTexture.loadFromFile("images\\DelPlayerButton.png")) {
        std::cerr << "Failed to load scoreButton texture" << std::endl;
    }
    deletePlayerButton.setPosition((currWindowWidth - deletePlayerButton.getSize().x) / 2, currWindowHeight / 2 + CHOOSE_PLAYER_SHIFT_BUTTON * 1.5);
    deletePlayerButton.setTexture(&deletePlayerButtonTexture, true);


    //Initialize dropBox
    sf::Font font;
    if (!font.loadFromFile("fonts\\ofont.ru_DS Crystal.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    players.loadFromFile();
    DropBox dropBox(font, players.createNameVector(), 300, 180, 200, 50, 4);


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
                    dropBox.update(players.createNameVector());
                }
            }
            dropBox.handleEvent(event);
        }
        chooseWindow.clear();
        chooseWindow.draw(backgroundChoosePlayerSprite);
        chooseWindow.draw(newPlayerButton);
        chooseWindow.draw(deletePlayerButton);
        dropBox.draw(chooseWindow);
        chooseWindow.display();
        if (!dropBox.getSelectedItem().empty()) {
            currentPlayer = players.getInfo(dropBox.getSelectedItem());
        }

    }


}
