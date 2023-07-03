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
    static void showMenu();
    static void about();
    void settings();

public:
    Game() : size(80, 20), symbol('#'), score(0){};
    virtual ~Game();
    bool isGameOver();
    bool init(std::pair<int, int> s);
    void logic();
    void print();
    void setSnake(const Snake &s);
    [[nodiscard]] const std::pair<int, int> &getSize() const;
    void setFood(const Food &f);
    bool isEatFood();
    void run();
    void start();
};

#endif//SNAKE_MAP_H
