#ifndef ROCKETCLASS_H
#define ROCKETCLASS_H

#include <SFML\Graphics.hpp>

class RocketClass {
public:
  RocketClass(float startX, float startY, bool cannon);
  sf::FloatRect getBounds();
  void draw(sf::RenderWindow &window);
  void update(bool cannon);

private:
  float speed;
  sf::Texture rocketTexture;
  sf::Sprite rocketSprite;
};

#endif //ROCKETCLASS_H
