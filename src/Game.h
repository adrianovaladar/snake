#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include "BestScores.h"
#include "Food.h"
#include "Graphics.h"
#include "Player.h"
#include "Snake.h"
#include "SuperFood.h"
#include <memory>

constexpr int defaultLength = 80;
constexpr int defaultWidth = 20;

constexpr int minLength = 10;
constexpr int minWidth = 5;
constexpr int maxLength = 1000;
constexpr int maxWidth = 1000;

constexpr char keyMoveUp = 'w';
constexpr char keyMoveLeft = 'a';
constexpr char keyMoveDown = 's';
constexpr char keyMoveRight = 'd';
constexpr char keyPause = 'p';
constexpr char keySave = 'm';

constexpr char symbolBordersOn = '#';
constexpr char symbolBordersOff = '.';

class Game final {
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
    void removeIfExists() const;
    bool borders;
    int foodsEaten;
    int velocity;
    bool logic();
    void changeVelocity();
    bool confirmSaveOverwrite() const;
    bool isGameOver() const;
    bool isRegularFoodEaten() const;
    bool isSuperFoodEaten() const;
    void settings(std::istream &input, std::ostream &output);
    void readSettings();
    void writeSettings() const;
    void save() const;
    void load();
    void updateGameFileName();
    bool hasBorders() const;
    void start();

public:
    Game();
    ~Game();
    void setSnake(const Snake &s);
    [[nodiscard]] const std::pair<int, int> &getSize() const;
    void setRegularFood(std::unique_ptr<Food> f);
    void setSuperFood(const std::weak_ptr<SuperFood> &f);
    void run();
    [[nodiscard]] const Snake &getSnake() const;
    [[nodiscard]] const Food &getRegularFood() const;
    [[nodiscard]] const Food &getSuperFood() const;
    void setBorders(bool b);
    friend class Graphics;
    friend class GameTests;
};

#endif//SNAKE_MAP_H
