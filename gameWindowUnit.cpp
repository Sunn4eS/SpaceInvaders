#include <SFML/Graphics.hpp>
#include "gameWindowUnit.h"


#include "RocketClass.h"
#include "CannonClass.h"

#include <iostream>

#include "AlienClass.h"
#include "TextureManagerClass.h"

#define GAME_WINDOW_WIDTH 1920
#define GAME_WINDOW_HEIGHT 1080


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
   // sf::Sprite heartSprite(TextureManager::getTexture("images\\Heart.png"));
   // heartSprite.setPosition(100, 100);
    int lives = 3;

    std::vector<sf::Sprite> hearts;
    for (int i = 0; i < lives; i++) {
        sf::Sprite heartSprite(TextureManager::getTexture("images\\Heart.png"));
        heartSprite.setPosition(75 * i + 100, 0);
        hearts.push_back(heartSprite);
    }



    //Pause Button


    //Rocket & Cannon initialization
    CannonClass cannon(windowSize.x / 2, 900);
    std::vector<RocketClass> rockets;

    // Alien initialization
    std::vector<AlienClass> aliens;
    std::vector<RocketClass> alienBullet;
    float alienSpeed = 100.0f;
    float alienAcceleration = 10.0f;
    float alienDirection = 1.0f;
    for (int i = 0; i < 10; i++) {
        aliens.emplace_back(ALIEN_SHIFT * i * 0.7, ALIEN_SHIFT, AlienColor::RED, 50);
        aliens.emplace_back(ALIEN_SHIFT * i * 0.7, ALIEN_SHIFT * 1.5, AlienColor::GREEN, 40);
        aliens.emplace_back(ALIEN_SHIFT * i * 0.7, ALIEN_SHIFT * 2, AlienColor::PURPLE, 30);
        aliens.emplace_back(ALIEN_SHIFT * i * 0.7, ALIEN_SHIFT * 2.5, AlienColor::BLUE, 20);
        aliens.emplace_back(ALIEN_SHIFT * i * 0.7, ALIEN_SHIFT * 3, AlienColor::YELLOW, 10);
    }

    //Main Cycle
    sf::Clock clock;
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
                    if (rockets.empty()) {
                        rockets.emplace_back(cannon.getBounds().left + cannon.getBounds().width / 2, cannon.getBounds().top, true);
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


        //Delete rockets
        rockets.erase(std::remove_if(rockets.begin(), rockets.end(), [](RocketClass& rocket){
            return rocket.getBounds().top < 0;
        }), rockets.end());

        //Delete alien Bullets
        alienBullet.erase(std::remove_if(alienBullet.begin(), alienBullet.end(), [&gameWindow](RocketClass& alien){
            return alien.getBounds().top > gameWindow.getSize().y;
        }), alienBullet.end());

        //Deleting rockets
        for (auto itRocket = rockets.begin(); itRocket != rockets.end(); ) {
            bool rocketRemoved = false;
            for (auto itAlien = aliens.begin(); itAlien != aliens.end(); ) {
                if (itRocket->getBounds().intersects(itAlien->getBounds())) {
                    itAlien = aliens.erase(itAlien);
                    itRocket = rockets.erase(itRocket);
                    rocketRemoved = true;
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
    //  gameWindow.draw(heartSprite);

        gameWindow.display();
    }
}
