#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include "BestScores.h"
#include "Player.h"
#include "RegularFood.h"
#include "Snake.h"
#include "SuperFood.h"
#include <memory>
#include <sstream>

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

#define SYMBOL_BORDERS_ON '#'
#define SYMBOL_BORDERS_OFF '.'

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
    void printHorizontalFence();
    bool readDirectionAndMoveSnake();
    void showMenu() const;
    static void about();
    void updateBestScores();
    void play();
    void showKeysAndSymbols();
    void removeIfExists();
    bool borders;
    std::stringstream bufferScreen;
    int foodsEaten;
    int velocity;
    bool logic();
    void printToBufferScreen();
    void changeVelocity();

public:
    Game();
    virtual ~Game();
    bool isGameOver();
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
    [[nodiscard]] const Snake &getSnake() const;
    [[nodiscard]] const Food &getRegularFood() const;
    [[nodiscard]] const Food &getSuperFood() const;
    void updateGameFileName();
    bool hasBorders() const;
    void setBorders(bool b);
};

#endif//SNAKE_MAP_H
