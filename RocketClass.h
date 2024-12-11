//
// Created by User on 11.12.2024.
//

#ifndef ROCKETCLASS_H
#define ROCKETCLASS_H

#include <SFML\Graphics.hpp>

class RocketClass {
public:
  RocketClass(float startX, float startY);
  sf::FloatRect getBounds();
  void draw(sf::RenderWindow &window);
  void update();

private:
  float speed;
  sf::Texture rocketTexture;
  sf::Sprite rocketSprite;
};



#endif //ROCKETCLASS_H
