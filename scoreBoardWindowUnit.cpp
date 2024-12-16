//
// Created by User on 16.12.2024.
//

#include "scoreBoardWindowUnit.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>

#include "fileModule.h"
#include "TextureManagerClass.h"
#define SCORE_BOARD_WINDOW_WIDTH 800
#define SCORE_BOARD_WINDOW_HEIGHT 900

void createScoreVector(std::vector<sf::Text> &scoreList, sf::Font &font, PlayerLinkedList &player) {

    font.loadFromFile("fonts\\ofont.ru_DS Crystal.ttf");
    PlayerLinkedList::player_t *currPlayer = player.head;
    while (currPlayer != nullptr) {
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(50);
        scoreText.setString(currPlayer->data.name + ": " + std::to_string(currPlayer->data.score));
        scoreText.setFillColor(sf::Color::White);
        scoreList.push_back(scoreText);
        currPlayer = currPlayer->next;
    }
    float startY = 330.0f;
    float spacing = 60.0f;
    for (size_t i = 0; i < scoreList.size(); i++) {
        scoreList[i].setPosition(sf::Vector2f(300, startY + i * spacing));
    }

}

void scoreBoard(PlayerLinkedList &players) {
    sf::RenderWindow scoreBoardWindow(sf::VideoMode(SCORE_BOARD_WINDOW_WIDTH, SCORE_BOARD_WINDOW_HEIGHT), "ScoreBoard");
    sf::Sprite backgroundSprite;
    sf::Vector2u textureSize = TextureManager::getTexture("images\\ScoreBackGround.png").getSize();
    sf::Vector2u windowSize = scoreBoardWindow.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);
    backgroundSprite.setTexture(TextureManager::getTexture("images\\ScoreBackGround.png"));

    std::vector<sf::Text> scoreList;
    sf::Font font;
    createScoreVector(scoreList, font, players);

    while (scoreBoardWindow.isOpen()) {
        sf::Event event;
        while (scoreBoardWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                scoreBoardWindow.close();
            }
            if (event.type == sf::Event::Resized) {
                sf::Vector2u windowSize;
                windowSize.x = SCORE_BOARD_WINDOW_WIDTH;
                windowSize.y = SCORE_BOARD_WINDOW_HEIGHT;
                scoreBoardWindow.setSize(windowSize);
            }
        }
        scoreBoardWindow.clear();
        scoreBoardWindow.draw(backgroundSprite);
        for (auto &scoreText : scoreList) {
            scoreBoardWindow.draw(scoreText);
        }
        scoreBoardWindow.display();
    }

}
