#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H

#include <utility>
#include <vector>

class Food {
protected:
    std::pair<int, int> position;
    char symbol;

public:
    explicit Food();
    virtual ~Food() = default;
    [[nodiscard]] char getSymbol() const;
    [[nodiscard]] const std::pair<int, int> &getPosition() const;
    void setPosition(const std::pair<int, int> &p);
    virtual void setPosition(const std::pair<int, int> &sizeMap, const std::vector<std::pair<int, int>> &positionsSnake) = 0;
};

#endif//SNAKE_FOOD_H
