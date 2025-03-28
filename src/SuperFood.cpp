#include "SuperFood.h"
#include <random>
#include <vector>
#include <algorithm>

SuperFood::SuperFood() : enabled(false), movesLeft(0) {
    this->symbol = 'F';
}

void SuperFood::setMovesLeft(const int moves) {
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
    std::uniform_real_distribution dis(0.0, 1.0);
    double probability = 0.2;
    if (dis(rng) <= probability) {
        Food::setPosition(sizeMap, positionsSnake, otherFoodPosition);
        enabled = true;
    }
}

bool SuperFood::isEnabled() const {
    return enabled;
}

void SuperFood::setEnabled(bool status) {
    enabled = status;
}

int SuperFood::getMovesLeft() const {
    return movesLeft;
}
