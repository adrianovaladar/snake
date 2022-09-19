//
// Created by Admin on 19/09/2022.
//

#include "Snake.h"
#include <vector>

Snake::Snake() {
    positionsSnake.push_back(std::make_pair(4, 4));
    positionsSnake.push_back(std::make_pair(3, 4));
    positionsSnake.push_back(std::make_pair(2, 4));
    symbol = 's';
}


char Snake::getSymbol() const {
    return symbol;
}

const std::vector<std::pair<int, int>> &Snake::getPositionsSnake() const {
    return positionsSnake;
}

