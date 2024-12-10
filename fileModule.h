//
// Created by User on 09.12.2024.
//

#ifndef FILEMODULE_H
#define FILEMODULE_H

#include <string>
#include <vector>


class PlayerLinkedList {
public:

    struct player_t {
        struct playerData_t {
            std::string name;
            int score;
        };
        playerData_t data;
        player_t *next;
    };
    player_t *head;
    PlayerLinkedList();
    ~PlayerLinkedList();

    void add(std::string &name, int score);
    void remove(const std::string &name);
    void saveToFile() const;
    void loadFromFile();
    std::vector<std::string> createNameVector() const;
    int getCount() const;
    void PlayerLinkedList::updateScore(std::string &name, int score);
};

extern PlayerLinkedList players;


#endif //FILEMODULE_H
