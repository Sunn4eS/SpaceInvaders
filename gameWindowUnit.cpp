#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameWindowUnit.h"
#include "choosePlayerWindow.h"
#include "RocketClass.h"
#include "CannonClass.h"
#include "AlienClass.h"
#include "TextureManagerClass.h"
#include "gameOverWindowUnit.h"
#include "pauseWindowUnit.h"

#define GAME_WINDOW_WIDTH 1920
#define GAME_WINDOW_HEIGHT 1080
#define PAUSE_BUTTON_WIDTH 100

void alienInitialization(std::vector<AlienClass>& aliens, float &alienSpeed, float &alienAcceleration, float &alienDirection) {
    alienSpeed = 100.0f;
    alienAcceleration = 10.0f;
    alienDirection = 1.0f;
    for (int i = 0; i < 10; i++) {
        aliens.emplace_back(ALIEN_SHIFT * i * 0.7, ALIEN_SHIFT, AlienColor::RED, 50);
        aliens.emplace_back(ALIEN_SHIFT * i * 0.7, ALIEN_SHIFT * 1.5, AlienColor::GREEN, 40);
        aliens.emplace_back(ALIEN_SHIFT * i * 0.7, ALIEN_SHIFT * 2, AlienColor::PURPLE, 30);
        aliens.emplace_back(ALIEN_SHIFT * i * 0.7, ALIEN_SHIFT * 2.5, AlienColor::BLUE, 20);
        aliens.emplace_back(ALIEN_SHIFT * i * 0.7, ALIEN_SHIFT * 3, AlienColor::YELLOW, 10);
    }
}

void scoreInitialization(int &score, sf::Text &scoreText, sf::Font &scoreFont) {
    score = 0;
    scoreFont.loadFromFile("fonts\\ofont.ru_DS Crystal.ttf");
    scoreText.setFont(scoreFont);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(60);
    scoreText.setColor(sf::Color::White);
    scoreText.setPosition(1500, 0);
}




void game() {
    sf::RenderWindow gameWindow(sf::VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT), "Construction of the game");
    sf::Vector2u windowSize = gameWindow.getSize();
    gameWindow.setFramerateLimit(120);
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("images\\BackGroundImage.png")) {
        std::cerr << "Failed to load background texture" << std::endl;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    //Lives
    sf::Texture heartTexture;
    int lives = 3;
    std::vector<sf::Sprite> hearts;
    for (int i = 0; i < lives; i++) {
        sf::Sprite heartSprite(TextureManager::getTexture("images\\Heart.png"));
        heartSprite.setPosition(75 * i + 100, 0);
        hearts.push_back(heartSprite);
    }
    //Score
    int score;
    sf::Text scoreText;
    sf::Font font;
    scoreInitialization(score, scoreText, font);

    //Pause Button
    sf::RectangleShape pauseButton(sf::Vector2f(PAUSE_BUTTON_WIDTH, PAUSE_BUTTON_WIDTH));
    sf::Texture pauseButtonTexture;
    if (!pauseButtonTexture.loadFromFile("images\\PauseButton.png")) {
        std::cerr << "Failed to load scoreButton texture" << std::endl;
    }
    pauseButton.setPosition(0, 0);
    pauseButton.setTexture(&pauseButtonTexture, true);

    //Rocket & Cannon initialization
    CannonClass cannon(windowSize.x / 2, 900);
    std::vector<RocketClass> rockets;

    // Alien initialization
    std::vector<RocketClass> alienBullet;
    std::vector<AlienClass> aliens;
    float alienSpeed;
    float alienAcceleration;
    float alienDirection;
    alienInitialization(aliens, alienSpeed, alienAcceleration, alienDirection);

    //Main Cycle
    sf::Clock clock;
    while (gameWindow.isOpen()) {
        sf::Event event{};
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
                     if (rockets.empty()) {
                        rockets.emplace_back(cannon.getBounds().left + cannon.getBounds().width / 2, cannon.getBounds().top, true);
                    }
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    pause();
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
                    if (isMouseOverButtonC(pauseButton, mousePos)) {
                        pause();
                    }
                }

            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            cannon.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            cannon.moveRight();
        }
        float deltaTime = clock.restart().asSeconds();

        cannon.update();
        for (auto& rocket : rockets) {
            rocket.update(true);
        }
        for (auto& alien : aliens) {
            alien.update(deltaTime, alienBullet);
        }
        for (auto& alienBullets : alienBullet) {
            alienBullets.update(false);
        }

        //Check edges
        bool hitEdge = false;
        for (const auto& alien : aliens) {
            if (alien.getBounds().left <= 0 || alien.getBounds().left + alien.getBounds().width >= gameWindow.getSize().x) {
                hitEdge = true;
                break;
            }
        }
        if (hitEdge) {
            for (auto& alien : aliens) {
                alien.setDirection(alienDirection * -1.0f, 0.0f);
            }
            for (auto& alien : aliens) {
                alien.setPosition(alien.getBounds().left, alien.getBounds().top + 50.0f);
            }

            alienSpeed += alienAcceleration;
            alienDirection *= -1.0f;
            for (auto& alien : aliens) {
                alien.setSpeed(alienSpeed);
            }
        }
        //


        //Delete rockets (bounds)
        rockets.erase(std::remove_if(rockets.begin(), rockets.end(), [](RocketClass& rocket){
            return rocket.getBounds().top < 0;
        }), rockets.end());

        //Delete alien Bullets (bounds)
        alienBullet.erase(std::remove_if(alienBullet.begin(), alienBullet.end(), [&gameWindow](RocketClass& alien){
            return alien.getBounds().top > gameWindow.getSize().y;
        }), alienBullet.end());

        //Delete alien bullets (cannon)

        for (auto itAlienRocket = alienBullet.begin(); itAlienRocket != alienBullet.end(); ){
            if (itAlienRocket->getBounds().intersects(cannon.getBounds())) {
                lives--;
                if (lives == 0) {
                    gameWindow.close();
                    gameOver();
                    if (currentPlayer->data.score < score) {
                        currentPlayer->data.score = score;
                    }
                    std::cout << "score "<< currentPlayer->data.score << "\n" << currentPlayer->data.name << "\n";

                }
                hearts.pop_back();
                //explosionSound.play();
                //explosions.emplace_back(cannon.getBounds().left, cannon.getBounds().top, explosionTexture);
                itAlienRocket = alienBullet.erase(itAlienRocket); // Удаление пули
            } else {
                ++itAlienRocket;
            }
        }


        alienBullet.erase(std::remove_if(alienBullet.begin(), alienBullet.end(), [&cannon, lives](RocketClass& alien) {
            if (alien.getBounds().intersects(cannon.getBounds())) {
              //  explosionSound.play();
              //  explosions.emplace_back(cannon.getBounds().left, cannon.getBounds().top, explosionTexture);

                return true;
                } return false;
        }),
        alienBullet.end());

        //Deleting rockets (aliens)
        for (auto itRocket = rockets.begin(); itRocket != rockets.end(); ) {
            bool rocketRemoved = false;
            for (auto itAlien = aliens.begin(); itAlien != aliens.end(); ) {
                if (itRocket->getBounds().intersects(itAlien->getBounds())) {
                    itAlien = aliens.erase(itAlien);
                    itRocket = rockets.erase(itRocket);
                    rocketRemoved = true;

                    score += itAlien->getScore();
                    scoreText.setString("Score: " + std::to_string(score));

                    if (aliens.empty()) {
                        alienInitialization(aliens, alienSpeed, alienAcceleration, alienDirection);
                    }
                    break;
                } else {
                    ++itAlien;
                }
            }
            if (!rocketRemoved) {
                ++itRocket;
            }
        }

        gameWindow.clear();
        gameWindow.draw(backgroundSprite);
        cannon.draw(gameWindow);
        for (auto& rocket : rockets) {
            rocket.draw(gameWindow);
        }

        for (auto& alien : aliens) {
            alien.draw(gameWindow);
        }
        for (auto& alien : alienBullet) {
            alien.draw(gameWindow);
        }
        for (auto& heart : hearts) {
            gameWindow.draw(heart);
        }
        gameWindow.draw(scoreText);
        gameWindow.draw(pauseButton);
        gameWindow.display();
    }
}
