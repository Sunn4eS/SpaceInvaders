//
// Created by User on 11.12.2024.
//

#ifndef ROCKETCLASS_H
#define ROCKETCLASS_H

#include <SFML\Graphics.hpp>

class RocketClass {
public:
  RocketClass() : lifes(3), rWidth(90), rHeight(90) {};


private:
  int lifes;
  int rWidth;
  int rHeight;
  sf::Texture rocketTexture;
  sf::Sprite rocketSprite;
  void loadTexture();
};



#endif //ROCKETCLASS_H
