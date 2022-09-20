#include <vector>

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H


class Snake {

private:
    std::vector<std::pair<int, int>> positionsSnake;
    char symbol {};
public:
    const std::vector<std::pair<int, int>> &getPositionsSnake() const;
    char getSymbol() const;
    explicit Snake();
    void move(char direction);
    void increaseSnake();
};


#endif //SNAKE_SNAKE_H