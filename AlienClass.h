//
// Created by User on 16.12.2024.
//

#ifndef ALIENCLASS_H
#define ALIENCLASS_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "RocketClass.h"


#define ALIEN_SHIFT 150
enum class AlienColor { RED, GREEN, PURPLE, BLUE, YELLOW};

class AlienClass {
public:
    AlienClass(float x, float y, AlienColor color, int score);
    void draw(sf::RenderWindow &window);
    void update(float deltaTime);
    sf::FloatRect getBounds() const;
    void setPosition(float x, float y);

    bool tryToShoot(std::vector<RocketClass> &bullets);

    void setDirection(float dirX, float dirY);

    void setSpeed(float newSpeed);

private:
    bool isKilled;
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    bool canShoot;
    float acceleration;
    sf::Vector2f direction;
    float shootTimer;
    float shootInterval;
};



#endif //ALIENCLASS_H
