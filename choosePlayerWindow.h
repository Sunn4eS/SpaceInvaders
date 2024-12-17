//
// Created by User on 07.12.2024.
//

#ifndef CHOOSEPLAYERWINDOW_H
#define CHOOSEPLAYERWINDOW_H
#include "fileModule.h"

void choosePlayer();
bool isMouseOverButtonC(const sf::RectangleShape& button, const sf::Vector2i& mousePos);

extern PlayerLinkedList::player_t* currentPlayer;

#endif //CHOOSEPLAYERWINDOW_H
