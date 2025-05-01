#include "Food.h"
#include "Utils.h"
#include <algorithm>
#include <random>
#include <vector>

char Food::getSymbol() const {
    return symbol;
}

const std::pair<int, int> &Food::getPosition() const {
    return position;
}

void Food::setPosition(const std::pair<int, int> &p) {
    Food::position = p;
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
        isSnakePosition = Utils::binarySearch(posSnake, foodPosition);
    } while (isSnakePosition || otherFoodPosition == foodPosition);

    this->position = foodPosition;
}
