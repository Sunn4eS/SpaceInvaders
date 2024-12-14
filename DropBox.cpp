//
// Created by User on 10.12.2024.
//

#include "DropBox.h"

#include <SFML/Window/Event.hpp>

DropBox::DropBox(sf::Font &fontI, const std::vector<std::string> &names, float x, float y, float width, float height, int visibleCount) : isOpen(false), selectedIndex(-1), scrollOffset(0) {
    font = fontI;
    mainRect.setSize(sf::Vector2f(width, height));
    mainRect.setPosition(x, y);
    mainRect.setFillColor(sf::Color::White);
    mainText.setOutlineColor(sf::Color::Yellow);
    mainText.setFont(font);
    mainText.setCharacterSize(46);
    mainText.setPosition(x + 5, y - 5);
    mainText.setFillColor(sf::Color::Black);
    for (const auto &name : names) {
        sf::Text text;
        text.setFont(font);
        text.setString(name);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Black);
        itemsTexts.push_back(text);
    }
    visibleItems = visibleCount;
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

        if (selectedIndex >= 0 && selectedIndex < itemsTexts.size()) {
            sf::RectangleShape rect(sf::Vector2f(mainRect.getSize().x, mainRect.getSize().y));
            rect.setPosition(itemsTexts[selectedIndex].getPosition().x - 5, itemsTexts[selectedIndex].getPosition().y - 5);
            rect.setFillColor(sf::Color::Green);
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
        rect.setOutlineColor(sf::Color::Yellow);
        itemsRects.push_back(rect);
        itemsTexts[i].setPosition(mainRect.getPosition().x + 5, mainRect.getPosition().y + (i + 1) * mainRect.getSize().y - 5);
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
                    mainRect.setFillColor(sf::Color::Yellow);
                    mainText.setString(itemsTexts[i].getString());
                    isOpen = false;
                    break;
                }
            }
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (isOpen) {
            if (event.key.code == sf::Keyboard::Up) {
                selectedIndex = std::max(0, selectedIndex - 1);
                mainText.setString(itemsTexts[selectedIndex].getString());
                updateItemsPosition();
            } else if (event.key.code == sf::Keyboard::Down) {
                selectedIndex = std::min(static_cast<int>(itemsTexts.size()) - 1, selectedIndex + 1);
                if (selectedIndex >= scrollOffset + visibleItems) {
                    scrollOffset = std::min(static_cast<int>(itemsTexts.size()) - visibleItems, scrollOffset);


                }
                mainText.setString(itemsTexts[selectedIndex].getString());
                updateItemsPosition();
            } else if (event.key.code == sf::Keyboard::Enter) {
                if (selectedIndex >= 0 && selectedIndex < itemsTexts.size()) {
                    mainRect.setFillColor(sf::Color::Yellow);
                    mainText.setString(itemsTexts[selectedIndex].getString());
                    isOpen = false;
                }
            }
        }
    }
}

void DropBox::clearMainField() {
    mainText.setString("");
}

void DropBox::update(std::vector<std::string> names) {
    itemsTexts.clear();
    for (const auto &name : names) {
        sf::Text text;
        text.setFont(font);
        text.setString(name);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Black);
        itemsTexts.push_back(text);
    }
    updateItemsPosition();
}

std::string DropBox::getSelectedItem() const {
    if (selectedIndex >= 0 && selectedIndex < itemsTexts.size()) {
        return itemsTexts[selectedIndex].getString();
    }
    return "";
}

