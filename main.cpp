#include <SFML/Graphics.hpp>
#include <iostream>
#include "choosePlayerWindow.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define BUTTON_WIDTH 350
#define BUTTON_HEIGHT 120
#define SHIFT_BUTTON 150

// Функция для проверки, попадает ли мышь на кнопку
bool isMouseOverButton(const sf::RectangleShape& button, const sf::Vector2i& mousePos) {
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

int main() {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Main Menu Example");
    sf::Vector2u windowSize = window.getSize();

    //Создание фонового изображения
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images\\StartMenuBackground.png")) {
        std::cerr << "Failed to load background texture" << std::endl;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Создание кнопок

    //Player Button
    sf::RectangleShape playerButton(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
    sf::Texture playerButtonTexture;
    if (!playerButtonTexture.loadFromFile("images\\playerButton.png")) {
        std::cerr << "Failed to load playButton texture" << std::endl;
    }
    playerButton.setPosition((windowSize.x - playerButton.getSize().x) / 2, windowSize.y / 2);
    playerButton.setTexture(&playerButtonTexture);

    //Start button
    sf::RectangleShape startButton(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
    sf::Texture startButtonTexture;
    if (!startButtonTexture.loadFromFile("images\\playButton.png")) {
        std::cerr << "Failed to load playButton texture" << std::endl;
    }
    startButton.setPosition((windowSize.x - startButton.getSize().x) / 2, windowSize.y / 2 - SHIFT_BUTTON);
    startButton.setTexture(&startButtonTexture, true);

    //Score Button
    sf::RectangleShape scoreButton(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
    sf::Texture scoreButtonTexture;
    if (!scoreButtonTexture.loadFromFile("images\\scoreButton.png")) {
        std::cerr << "Failed to load scoreButton texture" << std::endl;
    }
    scoreButton.setPosition((windowSize.x - scoreButton.getSize().x) / 2, windowSize.y / 2 + SHIFT_BUTTON);
    scoreButton.setTexture(&scoreButtonTexture, true);

    //Exit Button
    sf::RectangleShape exitButton(sf::Vector2f(150, 150));
    sf::Texture exitButtonTexture;
    if (!exitButtonTexture.loadFromFile("images\\exitButton.png")) {
        std::cerr << "Failed to load exitButton texture" << std::endl;
    }
    exitButton.setPosition((windowSize.x - exitButton.getSize().x) / 2 + SHIFT_BUTTON * 2, windowSize.y / 2 + SHIFT_BUTTON);
    exitButton.setTexture(&exitButtonTexture, true);


    // Main cycle
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            else if (event.type == sf::Event::Resized) {
                windowSize.x = WINDOW_WIDTH;
                windowSize.y = WINDOW_HEIGHT;
                window.setSize(windowSize);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (isMouseOverButton(startButton, mousePos)) {
                    std::cout << "Play button pressed!" << std::endl;
                }
                if (isMouseOverButton(exitButton, mousePos)) {
                    window.close();
                    //Save to file
                }
                if (isMouseOverButton(playerButton, mousePos)) {
                    choosePlayer();
                }
            }
            window.clear();
            window.draw(backgroundSprite);
            window.draw(startButton);
            window.draw(playerButton);
            window.draw(scoreButton);
            window.draw(exitButton);

            window.display();
        }
    }
    return 0;
}
