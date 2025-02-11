#ifndef SNAKE_SUPERFOOD_H
#define SNAKE_SUPERFOOD_H

#include "Food.h"
#include <utility>
#include <vector>

class SuperFood final : public Food {
private:
    bool enabled;
    int movesLeft;

public:
    explicit SuperFood();
    ~SuperFood() override = default;
    void setPosition(const std::pair<int, int> &sizeMap, const std::vector<std::pair<int, int>> &positionsSnake, const std::pair<int, int> &otherFoodPosition) override;
    void setMovesLeft(int moves);
    void decreaseMovesLeft();
    [[nodiscard]] bool isEnabled() const;
    void setEnabled(bool status);
    [[nodiscard]] int getMovesLeft() const;
};


#endif//SNAKE_SUPERFOOD_H
