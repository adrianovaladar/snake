#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <vector>
#include "Direction.h"

class Snake {

private:
    std::vector<std::pair<int, int>> positionsSnake;
    char symbol {};
    Direction direction;
public:
    explicit Snake();
    virtual ~Snake();
    [[nodiscard]] const std::vector<std::pair<int, int>> &getPositions() const;
    [[nodiscard]] Direction getDirection() const;
    void setDirection(Direction d);
    [[nodiscard]] char getSymbol() const;
    void move();
    void increase();
    void setSymbol(char s);
};


#endif //SNAKE_SNAKE_H