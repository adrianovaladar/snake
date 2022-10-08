#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include "Snake.h"
#include "Food.h"
#include "Player.h"


class Game {
private:
    int x;
    int y;
    char symbol;
    Snake snake;
    Food food;
    int score;
    const int sizeBestScores;
    void printVerticalFenceAndPlayableArea(int y);
    void printHorizontalFence();
    void readDirectionAndMoveSnake();
    bool isBestScore(std::vector<Player> players);
    void writeBestScore(std::vector<Player> players);
    std::vector<Player> readBestScores();
    void printBestScores(const std::vector<Player> &players);
    bool isEatFood();
public:
    bool isGameOver();
    Game() : x(0), y(0), symbol(0), score(0), sizeBestScores(5) {};
    void init(int i, int j, char symbolFence, char symbolSnake, char symbolFood);
    void logic();
    void print();
};

#endif //SNAKE_MAP_H
