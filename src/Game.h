#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include "BestScores.h"
#include "Food.h"
#include "Player.h"
#include "Snake.h"


class Game {
private:
    std::pair<int, int> size;
    Food food;
    Snake snake;
    BestScores bestScores;
    char symbol;
    int score;
    void printVerticalFenceAndPlayableArea(int y);
    void printHorizontalFence() const;
    void readDirectionAndMoveSnake();

public:
    Game() : size(10, 10), symbol(0), score(0){};
    virtual ~Game();
    bool isGameOver();
    bool init(int i, int j, char symbolFence, char symbolSnake, char symbolFood);
    void logic();
    void print();
    void setSnake(const Snake &s);
    [[nodiscard]] const std::pair<int, int> &getSize() const;
    void setFood(const Food &f);
    bool isEatFood();
};

#endif//SNAKE_MAP_H
