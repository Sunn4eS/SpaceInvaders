//
// Created by User on 10.12.2024.
//

#ifndef DROPBOX_H
#define DROPBOX_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "fileModule.h"


class DropBox {
public:
    DropBox(sf::Font &font, const std::vector<std::string> &names, float x, float y, float width, float, int visibleCount);
    void draw(sf::RenderWindow &window);
    void handleEvent(sf::Event &event);
    void update(std::vector<std::string> names);
    std::string getSelectedItem() const;

private:
    void updateItemsPosition();
    bool isOpen;
    int visibleItems;
    int selectedIndex;
    int scrollOffset;
    sf::RectangleShape mainRect;
    sf::Text mainText;
    std::vector<sf::RectangleShape> itemsRects;
    std::vector<sf::Text> itemsTexts;
    sf::Font font;
};


#endif //DROPBOX_H
