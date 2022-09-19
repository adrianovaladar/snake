//
// Created by Admin on 19/09/2022.
//

#include "Snake.h"
#include <vector>

Snake::Snake() {
    positionsSnake.push_back(std::make_pair(4, 4));
    positionsSnake.push_back(std::make_pair(3, 4));
    positionsSnake.push_back(std::make_pair(2, 4));
    symbol = 'o';
}


char Snake::getSymbol() const {
    return symbol;
}

const std::vector<std::pair<int, int>> &Snake::getPositionsSnake() const {
    return positionsSnake;
}

void Snake::moveRight() {
    std::vector<std::pair<int, int>>::iterator it = positionsSnake.begin();
    while(it != positionsSnake.end()) {
        (*it).first++;
        it++;
    }
}

