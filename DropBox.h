//
// Created by User on 10.12.2024.
//

#ifndef DROPBOX_H
#define DROPBOX_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class DropBox {
public:
    DropBox(sf::Font &font, const std::vector<std::string> &names, float x, float y, float width, float);
    void draw(sf::RenderWindow &window);
    void handleEvent(sf::Event &event);

private:
    void updateItemsPosition();
    bool isOpen;
    int selectedIndex;
    sf::RectangleShape mainRect;
    sf::Text mainText;
    std::vector<sf::RectangleShape> itemsRects;
    std::vector<sf::Text> itemsTexts;
};


#endif //DROPBOX_H
