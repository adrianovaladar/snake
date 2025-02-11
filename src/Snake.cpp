#include "Snake.h"
#include <vector>

Snake::Snake() : symbol{'o'}  {
  direction = Direction::RIGHT;
}

char Snake::getSymbol() const {
    return symbol;
}

const std::vector<std::pair<int, int>> &Snake::getPositions() const {
    return positions;
}

void updateHeadPosition(std::pair<int, int>& position, Direction direction, std::pair<int, int> sizeMap, bool border) {
    switch (direction) {
        case Direction::RIGHT:
            position.first = (!border && position.first > sizeMap.first - 2) ? 0 : position.first + 1;
            break;
        case Direction::LEFT:
            position.first = (!border && position.first < 1) ? sizeMap.first - 1 : position.first - 1;
            break;
        case Direction::UP:
            position.second = (!border && position.second < 1) ? sizeMap.second - 1 : position.second - 1;
            break;
        case Direction::DOWN:
            position.second = (!border && position.second > sizeMap.second - 2) ? 0 : position.second + 1;
            break;
        case Direction::NONE:
        default:
            break;
    }
}

void updateBodyPositions(std::pair<int,int> previousHeadPosition, std::vector<std::pair<int, int>>& positions) {
    std::pair<int, int> previousPosition = previousHeadPosition;
    for (auto it = positions.begin() + 1; it != positions.end(); ++it) {
        std::swap(*it, previousPosition);
    }
}

void Snake::move(const std::pair<int, int> &sizeMap, bool border) {
    std::pair<int, int> previousPosition = positions.at(0);
    updateHeadPosition(positions.at(0), direction, sizeMap, border);
    updateBodyPositions(previousPosition, positions);
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
