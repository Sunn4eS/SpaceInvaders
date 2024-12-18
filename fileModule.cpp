//
// Created by User on 09.12.2024.
//

#include "fileModule.h"
#include <string>
#include <fstream>
#include <vector>
PlayerLinkedList players;

PlayerLinkedList::PlayerLinkedList() : head(nullptr) {}
PlayerLinkedList::~PlayerLinkedList() {
    while (head != nullptr) {
        player_t *tmp = head;
        head = head->next;
        delete tmp;
    }
}

void PlayerLinkedList::add(std::string &name, int score) {
    auto *newPlayer = new player_t{{name, score},nullptr };
    if (head == nullptr) {
        head = newPlayer;
    } else {
        player_t *temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newPlayer;
    }
}

void PlayerLinkedList::remove(const std::string &name) {
    if (head == NULL) {
        return;
    }
    if (head->data.name == name) {
        player_t *temp = head;
        head = head->next;
        delete temp;
        return;
    }
    player_t *temp = head;
    while (temp->next && temp->next->data.name != name) {
        temp = temp->next;
    }
    if (temp->next) {
        player_t *tempRemove = temp->next;
        temp->next = temp->next->next;
        delete tempRemove;
    }
}

void PlayerLinkedList::saveToFile() const {
    std::ofstream file("playersData.bin", std::ios::binary);
    player_t *temp = head;
    while (temp) {
        size_t nameSize = temp->data.name.size();
        file.write(reinterpret_cast<char*>(&nameSize),sizeof(nameSize));
        file.write(temp->data.name.c_str(), nameSize);
        file.write(reinterpret_cast<char*>(&temp->data.score), sizeof(temp->data.score));
        temp = temp->next;
    }
    file.close();
}

void PlayerLinkedList::loadFromFile() {
    clear();
    std::ifstream file("playersData.bin", std::ios::binary);
    while (file) {
        size_t nameSize;
        file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        if (file.eof()) {
            break;
        }
        std::string name(nameSize, ' ');
        file.read(&name[0], nameSize);
        int score;
        file.read(reinterpret_cast<char*>(&score), sizeof(score));
        add(name, score);
    }
    file.close();
}

std::vector<std::string> PlayerLinkedList::createNameVector() const {
    player_t *temp = head;
    std::vector <std::string> nameVector;
    while (temp) {
        nameVector.push_back(temp->data.name);
        temp = temp->next;
    }
    return nameVector;
}

int PlayerLinkedList::getCount() const {
    player_t *temp = head;
    int count = 0;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

void PlayerLinkedList::updateScore(std::string &name, int score) const {
    player_t *temp = head;
    while (temp->data.name != name && temp) {
        temp = temp->next;
    }
    temp->data.score = score;
}

void PlayerLinkedList::clear() {
    while (head) {
        player_t *temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
}

PlayerLinkedList::player_t* PlayerLinkedList::getInfo(std::string name) {
    player_t *temp = head;
    while (temp && temp->data.name != name) {
        temp = temp->next;
    }
    return temp;
}






