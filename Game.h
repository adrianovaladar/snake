#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include "Snake.h"
#include "Food.h"


class Game {
private:
    int x;
    int y;
    char symbol;
    Snake snake;
    Food food;
    void printVerticalFenceAndPlayableArea(int y);
    void printHorizontalFence();
    bool isGameOver();
public:
    Game() : x(0), y(0), symbol(0) {}
    void init(int i, int j, char symbolFence, char symbolSnake, char symbolFood);
    void printMap();
};



#endif //SNAKE_MAP_H
