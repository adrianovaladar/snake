#include "Snake.h"
#include <vector>

Snake::Snake() : symbol {'o'}, direction {Direction::RIGHT} {
    positionsSnake.emplace_back(4, 4);
    positionsSnake.emplace_back(3, 4);
    positionsSnake.emplace_back(2, 4);
}

char Snake::getSymbol() const {
    return symbol;
}

const std::vector<std::pair<int, int>> &Snake::getPositions() const {
    return positionsSnake;
}

void Snake::move() {
    std::pair<int, int> previousPosition = positionsSnake.at(0);
    auto it = positionsSnake.begin();
    if (direction == Direction::RIGHT)
        positionsSnake.at(0).first++;
    else if (direction == Direction::LEFT)
        positionsSnake.at(0).first--;
    else if (direction == Direction::UP)
        positionsSnake.at(0).second--;
    else if(direction == Direction::DOWN)
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

void Snake::setSymbol(char s) {
    Snake::symbol = s;
}

Direction Snake::getDirection() const {
    return direction;
}

void Snake::setDirection(Direction d) {
    Snake::direction = d;
}

void Snake::increase() {
    positionsSnake.emplace_back(std::make_pair(-1, -1));
}

Snake::~Snake() = default;
