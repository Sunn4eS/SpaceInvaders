//
// Created by User on 11.12.2024.
//

#include "CannonClass.h"

CannonClass::CannonClass(float x, float y) : speed(8.0f) {
    cannonTexture.loadFromFile("images\\Cannon.png");
    cannonSprite.setTexture(cannonTexture);
    cannonSprite.setScale(6, 6);
    cannonSprite.setPosition(x, y);
}
void CannonClass::update() {
    if (cannonSprite.getPosition().x < 0) {
        cannonSprite.setPosition(0, cannonSprite.getPosition().y);
    } else if (cannonSprite.getPosition().x + cannonSprite.getGlobalBounds().width > 1900) {
        cannonSprite.setPosition(1900 - cannonSprite.getGlobalBounds().width, cannonSprite.getPosition().y);
    }
}
void CannonClass::draw(sf::RenderWindow &window) {
    window.draw(cannonSprite);
}

void CannonClass::moveLeft() {
    cannonSprite.move(-speed, 0);
}
void CannonClass::moveRight() {
    cannonSprite.move(speed, 0);
}

sf::FloatRect CannonClass::getBounds() {
    return cannonSprite.getGlobalBounds();
}

