#ifndef SNAKE_GAMETESTS_H
#define SNAKE_GAMETESTS_H

#include "../src/Game.h"
#include <gtest/gtest.h>

class GameTests : public ::testing::Test {
protected:
    Game game;
    Game game2;
    Snake snake;
    void SetUp() override {
    }

    void TearDown() override {
    }

    static void validateDirectionSnake(Snake &snake, const Direction d) {
        snake.validateDirection(d);
    }

    void readSettings() {
        game.readSettings();
    }
    void writeSettings() const {
        game.writeSettings();
    }

    void settings(std::istream &input, std::ostream &output) {
        game.settings(input, output);
    }

    void save() const {
        game.save();
    }

    void load() {
        game.load();
    }

    void load2() {
        game2.load();
    }

    void start() {
        game.start();
    }

    bool isGameOver() const {
        return game.isGameOver();
    }

    bool isRegularFoodEaten() const {
        return game.isRegularFoodEaten();
    }

    bool isRegularFoodEaten2() const {
        return game2.isRegularFoodEaten();
    }

    bool isSuperFoodEaten2() const {
        return game2.isSuperFoodEaten();
    }

    void updateGameFileName() {
        game.updateGameFileName();
    }

    void updateGameFileName2() {
        game2.updateGameFileName();
    }

    bool hasBorders2() const {
        return game2.hasBorders();
    }
};

#endif//SNAKE_GAMETESTS_H
