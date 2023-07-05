#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include "BestScores.h"
#include "Food.h"
#include "Player.h"
#include "Snake.h"

#define DEFAULT_WIDTH 80
#define DEFAULT_HEIGHT 20

class Game {
private:
    std::pair<int, int> size;
    Food food;
    Snake snake;
    BestScores bestScores;
    char symbol;
    int score;
    std::string settingsFileName;
    std::string directoryName;
    char keyMoveUp;
    char keymoveDown;
    char keyMoveLeft;
    char keyMoveRight;
    void printVerticalFenceAndPlayableArea(int y);
    void printHorizontalFence() const;
    void readDirectionAndMoveSnake();
    void showMenu() const;
    static void about();
    void updateBestScores();
    void play();
    void showKeys();

public:
    Game() : size(DEFAULT_WIDTH, DEFAULT_HEIGHT), symbol('#'), score(0), settingsFileName("settings"), directoryName("files"), keyMoveUp('w'), keymoveDown('s'), keyMoveLeft('a'), keyMoveRight('d'){};
    virtual ~Game();
    bool isGameOver();
    void logic();
    void print();
    void setSnake(const Snake &s);
    [[nodiscard]] const std::pair<int, int> &getSize() const;
    void setFood(const Food &f);
    bool isEatFood();
    void run();
    void start();
    void settings(std::istream &input, std::ostream &output);
    void readSettings();
    void writeSettings() const;
};

#endif//SNAKE_MAP_H
