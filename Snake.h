#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <vector>
#include "direction.h"

class Snake {

private:
    std::vector<std::pair<int, int>> positionsSnake;
    char symbol {};
    Direction direction;
public:
    explicit Snake();
    virtual ~Snake();
    const std::vector<std::pair<int, int>> &getPositions() const;
    Direction getDirection() const;
    void setDirection(Direction direction);
    char getSymbol() const;
    void move();
    void increase();
    void setSymbol(char s);
};


#endif //SNAKE_SNAKE_H