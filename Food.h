#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H


#include <utility>

class Food {
    std::pair<int, int> position;
    char symbol;
public:
    void setPosition(const std::pair<int, int> &position);
    void setSymbol(char symbol);
    char getSymbol() const;
    explicit Food();
    const std::pair<int, int> &getPosition() const;
    virtual ~Food();
};


#endif //SNAKE_FOOD_H
