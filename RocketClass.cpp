//
// Created by User on 11.12.2024.
//

#include "RocketClass.h"
#include "TextureManagerClass.h"
RocketClass::RocketClass(float startX, float startY, bool cannon) : speed(5.0f) {
    if (cannon) {
        rocketSprite.setTexture(TextureManager::getTexture("images\\BulletRocket.png"));
        rocketSprite.setScale(4, 4);
        speed = 8.0f;
    } else {
        rocketSprite.setTexture(TextureManager::getTexture("images\\AlienBullet.png"));
    }
    rocketSprite.setPosition(startX, startY);

}

void RocketClass::draw(sf::RenderWindow &window) {
    window.draw(rocketSprite);
}
void RocketClass::update(bool cannon) {
    if (cannon) {
        rocketSprite.move(0, -speed);
    } else {
        rocketSprite.move(0, speed);
    }
}

sf::FloatRect RocketClass::getBounds() {
  return rocketSprite.getGlobalBounds();
}