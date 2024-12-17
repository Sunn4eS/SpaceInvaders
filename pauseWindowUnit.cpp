#include "pauseWindowUnit.h"
#include "gameWindowUnit.h"



#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#define PAUSE_WINDOW_WIDTH 700
#define PAUSE_WINDOW_HEIGHT 600
#define BUTTON_WIDTH 250
#define BUTTON_HEIGHT 125
bool isMouseOverButtonP(const sf::RectangleShape& button, const sf::Vector2i& mousePos) {
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void pause(sf::RenderWindow &gameWindow) {
    sf::RenderWindow window(sf::VideoMode(PAUSE_WINDOW_WIDTH, PAUSE_WINDOW_HEIGHT), "Main Menu Example");
    sf::Vector2u windowSize = window.getSize();

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images\\PauseBackGround.png")) {
        std::cerr << "Failed to load background texture" << std::endl;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);

    sf::RectangleShape resumeButton(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
    createButton(resumeButton, 50, 430, "images\\ResumeButton.png");

    sf::RectangleShape exitButton(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
    createButton(exitButton, windowSize.x - exitButton.getSize().x - 50, 430, "images\\ExitFromPauseButton.png");

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                sf::Vector2u windowSize;
                windowSize.x = PAUSE_WINDOW_WIDTH;
                windowSize.y = PAUSE_WINDOW_HEIGHT;
                window.setSize(windowSize);
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (isMouseOverButtonP(resumeButton, mousePos)) {
                    window.close();
                }
                if (isMouseOverButtonP(exitButton, mousePos)) {
                    window.close();
                    gameWindow.close();

                }
                //      newPlayerWin();
                //      dropBox.update(players.createNameVector());


            }
            window.clear();
            window.draw(backgroundSprite);
            window.draw(resumeButton);
            window.draw(exitButton);

            window.display();


        }
    }
}
