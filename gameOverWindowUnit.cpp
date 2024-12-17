//
// Created by User on 16.12.2024.
//

#include "gameOverWindowUnit.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "TextureManagerClass.h"
#define GAME_OVER_WINDOW_WIDTH 800
#define GAME_OVER_WINDOW_HEIGHT 600

void gameOver() {
    sf::RenderWindow gameOverWindow(sf::VideoMode(GAME_OVER_WINDOW_WIDTH, GAME_OVER_WINDOW_HEIGHT), "GameOver");
    sf::Sprite backgroundSprite;
    sf::Vector2u textureSize = TextureManager::getTexture("images\\GameOver.png").getSize();
    sf::Vector2u windowSize = gameOverWindow.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);
    backgroundSprite.setTexture(TextureManager::getTexture("images\\GameOver.png"));

    while (gameOverWindow.isOpen()) {
        sf::Event event;
        while (gameOverWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameOverWindow.close();
            }
            if (event.type == sf::Event::Resized) {
                sf::Vector2u windowSize;
                windowSize.x = GAME_OVER_WINDOW_WIDTH;
                windowSize.y = GAME_OVER_WINDOW_HEIGHT;
                gameOverWindow.setSize(windowSize);
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape) {
                    gameOverWindow.close();
                }
            }
        }
        gameOverWindow.clear();
        gameOverWindow.draw(backgroundSprite);
        gameOverWindow.display();
    }
}
