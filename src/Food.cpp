#include "Food.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>


Food::Food() {
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
    do {
        srand(time(nullptr));
        foodPosition.first = std::rand() % sizeMap.first;
        foodPosition.second = std::rand() % sizeMap.second;
        isSnakePosition = std::binary_search(posSnake.begin(), posSnake.end(), foodPosition);
    } while (isSnakePosition);

    this->position = foodPosition;
}
