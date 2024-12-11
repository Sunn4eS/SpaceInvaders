//
// Created by User on 11.12.2024.
//

#include "RocketClass.h"
RocketClass::RocketClass(float startX, float startY) : speed(5.0f) {
    rocketTexture.loadFromFile("images\\BulletRocket.png");
    rocketSprite.setTexture(rocketTexture);
    rocketSprite.setPosition(startX, startY);
}

void RocketClass::draw(sf::RenderWindow &window) {
    window.draw(rocketSprite);
}
void RocketClass::update() {
    rocketSprite.move(0, -speed);
}
sf::FloatRect RocketClass::getBounds() {
  return rocketSprite.getGlobalBounds();
}