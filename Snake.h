#include <vector>

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H


class Snake {

private:
    std::vector<std::vector<int>> positionsSnake;
    char symbol {};
public:
    char getSymbol() const;

public:
    const std::vector<std::vector<int>> &getPositionsSnake() const;


public:
    explicit Snake();
    void moveUp();
    void moveDown();
    void moveRigth();
    void moveLeft();
    void increaseSnake();
};


#endif //SNAKE_SNAKE_H
/*
 *
 *
 *
 */