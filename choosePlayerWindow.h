#ifndef CHOOSEPLAYERWINDOW_H
#define CHOOSEPLAYERWINDOW_H
#include "fileModule.h"

void choosePlayer();
bool isMouseOverButtonC(const sf::RectangleShape& button, const sf::Vector2i& mousePos);

extern std::string currentPlayerName;
extern PlayerLinkedList::player_t* currentPlayer;

#endif //CHOOSEPLAYERWINDOW_H
