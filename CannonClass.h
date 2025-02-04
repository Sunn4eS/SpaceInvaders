#ifndef CANNONCLASS_H
#define CANNONCLASS_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


class CannonClass {
public:
    CannonClass(float x, float y);
    void update();
    void draw(sf::RenderWindow &window);
    sf::FloatRect getBounds();
    void moveLeft();
    void moveRight();
private:
    sf::Texture cannonTexture;
    sf::Sprite cannonSprite;
    float speed;
};



#endif //CANNONCLASS_H
