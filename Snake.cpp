//
// Created by Admin on 19/09/2022.
//

#include "Snake.h"
#include <vector>

Snake::Snake() {
    std::vector<int> x {4, 3, 2};
    std::vector<int> y {4, 4, 4};
    positionsSnake.push_back(x);
    positionsSnake.push_back(y);
    symbol = 's';
}

const std::vector<std::vector<int>> &Snake::getPositionsSnake() const {
    return positionsSnake;
}

char Snake::getSymbol() const {
    return symbol;
}

