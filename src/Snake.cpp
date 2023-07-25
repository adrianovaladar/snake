#include "Snake.h"
#include <vector>

Snake::Snake() : symbol{'o'}, direction{Direction::RIGHT}, positions{} {}

char Snake::getSymbol() const {
    return symbol;
}

const std::vector<std::pair<int, int>> &Snake::getPositions() const {
    return positions;
}

void Snake::move(const std::pair<int, int> &sizeMap, bool border) {
    std::pair<int, int> previousPosition = positions.at(0);
    auto it = positions.begin();
    if (direction == Direction::RIGHT) {
        if (!border && positions.at(0).first > sizeMap.first - 2) {
            positions.at(0).first = 0;
        } else {
            positions.at(0).first++;
        }
    } else if (direction == Direction::LEFT) {
        if (!border && positions.at(0).first < 1) {
            positions.at(0).first = sizeMap.first - 1;
        } else {
            positions.at(0).first--;
        }
    } else if (direction == Direction::UP) {
        if (!border && positions.at(0).second < 1) {
            positions.at(0).second = sizeMap.second - 1;
        } else {
            positions.at(0).second--;
        }
    } else if (direction == Direction::DOWN) {
        if (!border && positions.at(0).second > sizeMap.second - 2) {
            positions.at(0).second = 0;
        } else {
            positions.at(0).second++;
        }
    }
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

Direction Snake::getDirection() const {
    return direction;
}

void Snake::setDirection(Direction d) {
    Snake::direction = d;
}

Snake &Snake::operator++() {
    positions.emplace_back(-1, -1);
    return *this;
}

Snake::~Snake() = default;

void Snake::validateDirection(Direction d) {
    switch (d) {
        case Direction::UP: {
            if (direction != Direction::DOWN)
                direction = Direction::UP;
            break;
        }
        case Direction::LEFT: {
            if (direction != Direction::RIGHT)
                direction = Direction::LEFT;
            break;
        }
        case Direction::DOWN: {
            if (direction != Direction::UP)
                direction = Direction::DOWN;
            break;
        }
        case Direction::RIGHT: {
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
    positions.emplace_back(sizeMap.first / 2, sizeMap.second / 2);
    positions.emplace_back(sizeMap.first / 2 - 1, sizeMap.second / 2);
    positions.emplace_back(sizeMap.first / 2 - 2, sizeMap.second / 2);
}
