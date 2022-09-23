#include <vector>

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H


class Snake {

private:
    std::vector<std::pair<int, int>> positionsSnake;
    char symbol {};
public:
    const std::vector<std::pair<int, int>> &getPositions() const;
    char getSymbol() const;
    explicit Snake();
    void move(char direction);
    void increase();
    void setSymbol(char symbol);
};


#endif //SNAKE_SNAKE_H