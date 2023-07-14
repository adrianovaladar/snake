#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include "BestScores.h"
#include "Player.h"
#include "RegularFood.h"
#include "Snake.h"
#include "SuperFood.h"
#include <memory>

#define DEFAULT_LENGTH 80
#define DEFAULT_WIDTH 20

#define MIN_LENGTH 10
#define MIN_WIDTH 5

#define KEY_MOVE_UP 'w'
#define KEY_MOVE_LEFT 'a'
#define KEY_MOVE_DOWN 's'
#define KEY_MOVE_RIGHT 'd'
#define KEY_PAUSE 'p'
#define KEY_SAVE 'm'

class Game {
private:
    std::pair<int, int> size;
    std::unique_ptr<Food> regularFood;
    std::unique_ptr<Food> superFood;
    Snake snake;
    BestScores bestScores;
    char symbol;
    int score;
    std::string settingsFileName;
    std::string directoryName;
    std::string gameFileName;
    bool pause;
    void printVerticalFenceAndPlayableArea(int y);
    void printHorizontalFence() const;
    bool readDirectionAndMoveSnake();
    void showMenu() const;
    static void about();
    void updateBestScores();
    void play();
    static void showKeys();
    void removeIfExists();

public:
    Game();
    virtual ~Game();
    bool isGameOver();
    bool logic();
    void print();
    void setSnake(const Snake &s);
    [[nodiscard]] const std::pair<int, int> &getSize() const;
    void setRegularFood(std::unique_ptr<Food> f);
    void setSuperFood(std::unique_ptr<Food> f);
    bool isEatRegularFood();
    bool isEatSuperFood();
    void run();
    void start();
    void settings(std::istream &input, std::ostream &output);
    void readSettings();
    void writeSettings() const;
    void save();
    void load();
    [[nodiscard]] int getScore() const;
    [[nodiscard]] const Snake &getSnake() const;
    [[nodiscard]] const Food &getFood() const;
    void updateGameFileName();
};

#endif//SNAKE_MAP_H
