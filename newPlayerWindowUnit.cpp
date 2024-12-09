//
// Created by User on 09.12.2024.
//
#include <SFML/Graphics.hpp>
#include "newPlayerWindowUnit.h"
#include <iostream>
#include "fileModule.h"

#define NEW_PLAYER_WINDOW_WIDTH 650
#define NEW_PLAYER_WINDOW_HEIGHT 400
#define NEW_PLAYER_OK_BUTTON_WIDTH 140
#define NEW_PLAYER_OK_BUTTON_HEIGHT 80

bool isMouseOverButtonOk(const sf::RectangleShape& button, const sf::Vector2i& mousePos) {
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void newPlayerWin() {

    sf::RenderWindow newPlayerWindow(sf::VideoMode (NEW_PLAYER_WINDOW_WIDTH, NEW_PLAYER_WINDOW_HEIGHT ), "New Player");
    int currWindowWidth = newPlayerWindow.getSize().x;
    int currWindowHeight = newPlayerWindow.getSize().y;
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


    //input Edit
    sf::Font font;
    if (!font.loadFromFile("fonts\\ofont.ru_DS Crystal.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    sf::Text newNameEdit;
    newNameEdit.setFont(font);
    newNameEdit.setCharacterSize(65);
    newNameEdit.setFillColor(sf::Color::White);
    newNameEdit.setPosition(220, 190);
    std::string newNameStr;


    //ok button
    sf::RectangleShape okButton(sf::Vector2f(NEW_PLAYER_OK_BUTTON_WIDTH, NEW_PLAYER_OK_BUTTON_HEIGHT));
    sf::Texture okButtonTexture;
    if (!okButtonTexture.loadFromFile("images\\OkButton.png")) {
        std::cerr << "Failed to load scoreButton texture" << std::endl;
    }
    okButton.setPosition((currWindowWidth - okButton.getSize().x) / 2 + 200, currWindowHeight / 2 + 100);
    okButton.setTexture(&okButtonTexture, true);


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
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !newNameStr.empty()) {
                    newNameStr.pop_back();
                } else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                    newNameStr += static_cast<char>(event.text.unicode);
                }
                newNameEdit.setString(newNameStr);
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(newPlayerWindow);
                if (isMouseOverButtonOk(okButton, mousePos)) {
                    //add new player
                    players.add(newNameStr, 0);
                    players.saveToFile();
                    newPlayerWindow.close();
                }
            }



        }

        newPlayerWindow.clear();
        newPlayerWindow.draw(backgroundNewPlayerSprite);
        newPlayerWindow.draw(newNameEdit);
        if (!newNameStr.empty()){
            newPlayerWindow.draw(okButton);
        }

        newPlayerWindow.display();

    }
}
