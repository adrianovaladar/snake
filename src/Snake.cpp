#include "Snake.h"
#include <vector>

Snake::Snake() : symbol{'o'}, direction{Direction::RIGHT}, positions{} {}

char Snake::getSymbol() const {
    return symbol;
}

const std::vector<std::pair<int, int>> &Snake::getPositions() const {
    return positions;
}

void Snake::move() {
    std::pair<int, int> previousPosition = positions.at(0);
    auto it = positions.begin();
    if (direction == Direction::RIGHT)
        positions.at(0).first++;
    else if (direction == Direction::LEFT)
        positions.at(0).first--;
    else if (direction == Direction::UP)
        positions.at(0).second--;
    else if (direction == Direction::DOWN)
        positions.at(0).second++;
    while (it != positions.end()) {
        if (it == positions.begin()) {
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
    positions.emplace_back(-1, -1);
}

Snake::~Snake() = default;

void Snake::validateDirection(int c) {
    switch (c) {
        case 'w': {
            if (direction != Direction::DOWN)
                direction = Direction::UP;
            break;
        }
        case 'a': {
            if (direction != Direction::RIGHT)
                direction = Direction::LEFT;
            break;
        }
        case 's': {
            if (direction != Direction::UP)
                direction = Direction::DOWN;
            break;
        }
        case 'd': {
            if (direction != Direction::LEFT)
                direction = Direction::RIGHT;
            break;
        }
        default: {
            break;
        }
    }
}

void Snake::setPositions(const std::vector<std::pair<int, int>> &pS) {
    Snake::positions = pS;
}

void Snake::setPositions(const std::pair<int, int> &sizeMap) {
    positions.clear();
    positions.emplace_back(sizeMap.first / 2.5, sizeMap.second / 2.5);
    positions.emplace_back(sizeMap.first / 2.5 - 1, sizeMap.second / 2.5);
    positions.emplace_back(sizeMap.first / 2.5 - 2, sizeMap.second / 2.5);
}
