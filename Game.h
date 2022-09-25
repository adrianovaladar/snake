#include "Snake.h"

#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H


class Game {
private:
    int x;
    int y;
    char symbol;
    Snake snake;
public:
    Game() : x(0), y(0), symbol(0) {}
    void init(int i, int j, char symbolFence, char symbolSnake, char symbolFood);
    void printMap();
    void printVerticalFenceAndPlayableArea(int y);
    void printHorizontalFence();
};



#endif //SNAKE_MAP_H
