#ifndef SNAKE_GAMETESTS_H
#define SNAKE_GAMETESTS_H

#include "../src/Game.h"
#include <gtest/gtest.h>

class GameTests : public ::testing::Test {
protected:

    void SetUp() override {
    }

    void TearDown() override {
    }

    void validateDirectionSnake(Snake &snake, Direction d) {
        snake.validateDirection(d);
    }

};

#endif//SNAKE_GAMETESTS_H
