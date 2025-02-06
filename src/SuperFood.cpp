#include "SuperFood.h"
#include <random>
#include <vector>
#include <algorithm>

SuperFood::SuperFood() : enabled(false), movesLeft(0) {
    this->symbol = 'F';
}

void SuperFood::setMovesLeft(int moves) {
    movesLeft = moves;
}

void SuperFood::decreaseMovesLeft() {
    movesLeft--;
    if (movesLeft == 0) {
        enabled = false;
        position = {-1, -1};
    }
}

void SuperFood::setPosition(const std::pair<int, int> &sizeMap, const std::vector<std::pair<int, int>> &positionsSnake, const std::pair<int, int> &otherFoodPosition) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double probability = 0.2;
    if (dis(rng) <= probability) {
        std::pair<int, int> superFoodPosition;
        std::vector<std::pair<int, int>> posSnake = positionsSnake;
        std::sort(posSnake.begin(), posSnake.end());
        bool isSnakePosition;
        do {
            std::uniform_int_distribution<int> distX(0, sizeMap.first - 1);
            std::uniform_int_distribution<int> distY(0, sizeMap.second - 1);
            superFoodPosition.first = distX(rng);
            superFoodPosition.second = distY(rng);
            isSnakePosition = std::binary_search(posSnake.begin(), posSnake.end(), superFoodPosition);
        } while (isSnakePosition || otherFoodPosition == superFoodPosition);

        this->position = superFoodPosition;
        enabled = true;
    }
}

bool SuperFood::isEnabled() const {
    return enabled;
}

void SuperFood::setEnabled(bool status) {
    SuperFood::enabled = status;
}

int SuperFood::getMovesLeft() const {
    return movesLeft;
}
