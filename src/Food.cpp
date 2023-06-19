#include "Food.h"
#include <random>
#include <vector>

Food::Food() : symbol{'f'} {
    position = std::make_pair(0, 0);
}

Food::~Food() = default;

char Food::getSymbol() const {
    return symbol;
}

const std::pair<int, int> &Food::getPosition() const {
    return position;
}

void Food::setSymbol(char s) {
    Food::symbol = s;
}

void Food::setPosition(const std::pair<int, int> &sizeMap, const std::vector<std::pair<int, int>> &positionsSnake) {

    std::pair<int, int> foodPosition;
    std::vector<std::pair<int, int>> posSnake = positionsSnake;
    std::sort(posSnake.begin(), posSnake.end());
    bool isSnakePosition;
    std::random_device dev;
    std::mt19937 rng(dev());
    do {
        std::uniform_int_distribution<int> distX(0, sizeMap.first - 1);
        std::uniform_int_distribution<int> distY(0, sizeMap.second - 1);
        foodPosition.first = distX(rng);
        foodPosition.second = distY(rng);
        isSnakePosition = std::binary_search(posSnake.begin(), posSnake.end(), foodPosition);
    } while (isSnakePosition);

    this->position = foodPosition;
}
