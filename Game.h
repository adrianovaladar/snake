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
    Game(int x, int y, char symbol) : x(x), y(y), symbol(symbol) {}
    void drawMap();
    void printVerticalFence(int y);
    void printHorizontalFence();
};



#endif //SNAKE_MAP_H
