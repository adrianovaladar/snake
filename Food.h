#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H


#include <utility>

class Food {
    std::pair<int, int> position;
    char symbol;
public:
    explicit Food();
    virtual ~Food();
    void setPosition(const std::pair<int, int> &sizeMap, const std::vector<std::pair<int, int>> &positionsSnake);
    void setSymbol(char s);
    [[nodiscard]] char getSymbol() const;
    [[nodiscard]] const std::pair<int, int> &getPosition() const;
};


#endif //SNAKE_FOOD_H
