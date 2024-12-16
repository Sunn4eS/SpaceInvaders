#include "AlienClass.h"
#include "TextureManagerClass.h"
#include <iostream>
#include <ostream>


AlienClass::AlienClass(float x, float y, AlienColor color, int score) : isKilled(false), speed(100.0f), acceleration(1), direction(1.0f, 0.0f) {
    std::string texturePath;
    switch (color) {
        case AlienColor::RED: {
            texturePath = "images/RedAlien.png";
            canShoot = true;
            break;
        }
        case AlienColor::GREEN: {
            texturePath = "images/GreenAlien.png";
            canShoot = false;
            break;
        }
        case AlienColor::PURPLE: {
            texturePath = "images/PurpleAlien.png";
            canShoot = false;
            break;
        }
        case AlienColor::BLUE: {
            texturePath = "images/BlueAlien.png";
            canShoot = false;
            break;
        }
        case AlienColor::YELLOW: {
            texturePath = "images/YellowAlien.png";
            canShoot = false;
            break;
        }
    }
    try {
        sprite.setTexture(TextureManager::getTexture(texturePath));
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl; throw;
    }

    sprite.setPosition(x, y);
    std::cout << "Alien created at (" << x << ", " << y << ") with texture " << texturePath << std::endl;
}

void AlienClass::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void AlienClass::update(float deltaTime) {
    sprite.move(speed * direction.x * deltaTime, speed * direction.y * deltaTime);
}

sf::FloatRect AlienClass::getBounds() const {
    return sprite.getGlobalBounds();
}
void AlienClass::setDirection(float dirX, float dirY) {
    direction.x = dirX;
    direction.y = dirY;
}
void AlienClass::setSpeed(float newSpeed) {
    speed = newSpeed;
}
void AlienClass::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}



