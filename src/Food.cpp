#include "Food.h"
#include <random>
#include <vector>
#include <algorithm>

Food::Food() : position(std::make_pair(-1, -1)), symbol('f') {}

char Food::getSymbol() const {
    return symbol;
}

const std::pair<int, int> &Food::getPosition() const {
    return position;
}

void Food::setPosition(const std::pair<int, int> &p) {
    Food::position = p;
}

bool binarySearch (const std::vector<std::pair<int, int>> &posSnake, const std::pair<int, int> &foodPosition) {
    int begin = 0;
    auto end = static_cast<int>(posSnake.size()) - 1;

    while (begin <= end) {
        const auto middle = std::midpoint(begin, end);// begin + (end - begin) / 2;
        if (foodPosition == posSnake.at(middle)) {
            return  true;
        }
        if (foodPosition < posSnake.at(middle)) {
            end = middle-1;
        } else {
            begin = middle+1;
        }
    }
    return false;
}

void Food::setPosition(const std::pair<int, int> &sizeMap, const std::vector<std::pair<int, int>> &positionsSnake, const std::pair<int, int> &otherFoodPosition) {
    std::pair<int, int> foodPosition;
    std::vector<std::pair<int, int>> posSnake = positionsSnake;
    std::ranges::sort(posSnake);
    bool isSnakePosition;
    std::random_device dev;
    std::mt19937 rng(dev());
    do {
        std::uniform_int_distribution distX(0, sizeMap.first - 1);
        std::uniform_int_distribution distY(0, sizeMap.second - 1);
        foodPosition.first = distX(rng);
        foodPosition.second = distY(rng);
        isSnakePosition = binarySearch(posSnake, foodPosition);
    } while (isSnakePosition || otherFoodPosition == foodPosition);

    this->position = foodPosition;
}
