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

const std::vector<std::pair<int, int>> &Snake::getPositions() const {
    return positionsSnake;
}

void Snake::move(char direction) {
    std::pair<int, int> previousPosition = positionsSnake.at(0);
    std::vector<std::pair<int, int>>::iterator it = positionsSnake.begin();
    if (direction == 'r')
        positionsSnake.at(0).first++;
    else if (direction == 'l')
        positionsSnake.at(0).first--;
    else if (direction == 'u')
        positionsSnake.at(0).second--;
    else if(direction == 'd')
        positionsSnake.at(0).second++;
    while (it != positionsSnake.end()) {
        if (it == positionsSnake.begin()) {
            it++;
            continue;
        }
        std::pair<int, int> tmp = *it;
        *it = previousPosition;
        previousPosition = tmp;
        it++;
    }
}

void Snake::setSymbol(char symbol) {
    Snake::symbol = symbol;
}
