#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include "BestScores.h"
#include "Food.h"
#include "Graphics.h"
#include "Player.h"
#include "Snake.h"
#include "SuperFood.h"
#include <memory>
#include <sstream>

#define DEFAULT_LENGTH 80
#define DEFAULT_WIDTH 20

#define MIN_LENGTH 10
#define MIN_WIDTH 5
#define MAX_LENGTH 1000
#define MAX_WIDTH 1000

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
    std::unique_ptr<Food> food;
    std::shared_ptr<SuperFood> superFood;
    Snake snake;
    Graphics graphics;
    BestScores bestScores;
    char symbol;
    int score;
    std::string settingsFileName;
    std::string directoryName;
    std::string gameFileName;
    bool pause;
    bool kbHit;
    bool readKey();
    void updateBestScores();
    void play();
    void removeIfExists();
    bool borders;
    int foodsEaten;
    int velocity;
    bool logic();
    void changeVelocity();

public:
    Game();
    virtual ~Game();
    bool isGameOver();
    void setSnake(const Snake &s);
    [[nodiscard]] const std::pair<int, int> &getSize() const;
    void setRegularFood(std::unique_ptr<Food> f);
    void setSuperFood(const std::weak_ptr<SuperFood> &f);
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
    friend class Graphics;
};

#endif//SNAKE_MAP_H
