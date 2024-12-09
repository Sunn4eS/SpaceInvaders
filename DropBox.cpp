//
// Created by User on 10.12.2024.
//

#include "DropBox.h"

#include <SFML/Window/Event.hpp>

DropBox::DropBox(sf::Font &font, const std::vector<std::string> &names, float x, float y, float width, float height) : isOpen(false), selectedIndex(-1) {
    mainRect.setSize(sf::Vector2f(width, height));
    mainRect.setPosition(x, y);
    mainRect.setFillColor(sf::Color::White);
    mainText.setFont(font);
    mainText.setCharacterSize(40);
    mainText.setPosition(x + 10, y + 10);
    mainText.setFillColor(sf::Color::Black);

    for (const auto &name : names) {
        sf::Text text;
        text.setFont(font);
        text.setString(name);
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::Black);
        itemsTexts.push_back(text);
    }
    updateItemsPosition();
}

void DropBox::draw(sf::RenderWindow &window) {
    window.draw(mainRect);
    window.draw(mainText);

    if (isOpen) {
        for (const auto &rect : itemsRects) {
            window.draw(rect);
        }
        for (const auto &texts : itemsTexts) {
            window.draw(texts);
        }
    }
}

void DropBox::updateItemsPosition() {
    itemsRects.clear();
    for (size_t i = 0; i < itemsTexts.size(); i++) {
        sf::RectangleShape rect;
        rect.setSize(mainRect.getSize());
        rect.setPosition(mainText.getPosition().x, mainText.getPosition().y + (i + 1) * mainRect.getSize().y);
        rect.setFillColor(sf::Color::White);
        itemsRects.push_back(rect);
        itemsTexts[i].setPosition(mainRect.getPosition().x + 5, mainRect.getPosition().y + (i + 1) * mainRect.getSize().y + 5);
    }
}

void DropBox::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        float mouseX = static_cast<float>(event.mouseButton.x);
        float mouseY = static_cast<float>(event.mouseButton.y);
        if (mainRect.getGlobalBounds().contains(mouseX, mouseY)) {
            isOpen = !isOpen;
        } else if (isOpen) {
            for (size_t i = 0; i < itemsTexts.size(); ++i) {
                if (itemsTexts[i].getGlobalBounds().contains(mouseX, mouseY)) {
                    selectedIndex = static_cast<int>(i);
                    mainText.setString(itemsTexts[i].getString());
                    isOpen = false;
                    break;
                }
            }
        }
    }
}

