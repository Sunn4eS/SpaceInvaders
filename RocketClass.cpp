//
// Created by User on 11.12.2024.
//

#include "RocketClass.h"

void RocketClass::loadTexture() {
    rocketTexture.loadFromFile("images\\Rocket.png");
    rocketSprite.setTexture(rocketTexture);
}