#include "RegularFood.h"
#include <random>
#include <vector>

RegularFood::RegularFood() {
    this->symbol = 'f';
}

void RegularFood::setPosition(const std::pair<int, int> &sizeMap, const std::vector<std::pair<int, int>> &positionsSnake) {

    std::pair<int, int> RegularFoodPosition;
    std::vector<std::pair<int, int>> posSnake = positionsSnake;
    std::sort(posSnake.begin(), posSnake.end());
    bool isSnakePosition;
    std::random_device dev;
    std::mt19937 rng(dev());
    do {
        std::uniform_int_distribution<int> distX(0, sizeMap.first - 1);
        std::uniform_int_distribution<int> distY(0, sizeMap.second - 1);
        RegularFoodPosition.first = distX(rng);
        RegularFoodPosition.second = distY(rng);
        isSnakePosition = std::binary_search(posSnake.begin(), posSnake.end(), RegularFoodPosition);
    } while (isSnakePosition);

    this->position = RegularFoodPosition;
}
