#ifndef SNAKE_REGULARFOOD_H
#define SNAKE_REGULARFOOD_H


#include "Food.h"
#include <utility>
#include <vector>

class RegularFood : public Food {
public:
    explicit RegularFood();
    ~RegularFood() override = default;
    void setPosition(const std::pair<int, int> &sizeMap, const std::vector<std::pair<int, int>> &positionsSnake, const std::pair<int, int> &otherFoodPosition) override;
};

#endif//SNAKE_REGULARFOOD_H
