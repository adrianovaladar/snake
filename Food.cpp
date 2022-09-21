#include <vector>
#include <cstdlib>
#include <algorithm>
#include "Food.h"

Food::Food() {
    position = std::make_pair(0, 0);
}

Food::~Food() {

}

char Food::getSymbol() const {
    return symbol;
}

const std::pair<int, int> &Food::getPosition() const {
    return position;
}

void Food::setSymbol(char symbol) {
    Food::symbol = symbol;
}

void Food::setPosition(const std::pair<int, int> &sizeMap, const std::vector<std::pair<int, int>> &positionsSnake) {

    std::pair<int, int> foodPosition;
    std::vector<std::pair<int, int>> posSnake = positionsSnake;
    std::vector<std::pair<int, int>>::iterator it;
    bool pos = false;
    do {
        foodPosition.first = std::rand() % sizeMap.first;
        foodPosition.second = std::rand() % sizeMap.second;
        pos = std::binary_search(posSnake.begin(), posSnake.end(), foodPosition);
    } while (pos);

    this->position = foodPosition;

}
