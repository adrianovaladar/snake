#ifndef SNAKE_SNAKETESTS_H
#define SNAKE_SNAKETESTS_H

#include "../src/Game.h"
#include <gtest/gtest.h>

class SnakeTests : public ::testing::Test {
protected:
    Snake snake;
    void SetUp() override {
    }

    void TearDown() override {
    }

    void setPositions(const std::vector<std::pair<int, int>> &pS) {
        snake.setPositions(pS);
    }
};

#endif//SNAKE_SNAKETESTS_H
