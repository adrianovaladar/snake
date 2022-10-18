#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include "Snake.h"
#include "Food.h"
#include "Player.h"
#include "BestScores.h"


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
    bool isEatFood();
public:
    Game() : size(0 ,0), symbol(0), score(0) {};
    virtual ~Game();
    bool isGameOver();
    bool init(int i, int j, char symbolFence, char symbolSnake, char symbolFood);
    void logic();
    void print();
};

#endif //SNAKE_MAP_H
