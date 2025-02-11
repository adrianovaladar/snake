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

    void move(const std::pair<int, int> &sizeMap, bool border) {
        snake.move(sizeMap,border);
    }
    void validateDirection(Direction d) {
        snake.validateDirection(d);
    }

    void moveTests(Direction d, std::pair<int, int> expectedPosition, bool isBorderOn) {
        snake.setDirection(d);
        move({80, 20}, isBorderOn);
        EXPECT_EQ(expectedPosition, snake.getPositions().front());
    }

    void runDirectionValidationTest(Direction initialDirection,
                                    const std::vector<Direction>& directionChanges,
                                    const std::vector<std::pair<int, Direction>>& expectedOutcomes) {
        snake.setPositions({{2, 2}});
        snake.setDirection(initialDirection);
        for (size_t i = 0; i < directionChanges.size(); ++i) {
            validateDirection(directionChanges[i]);
            for (const auto& outcome : expectedOutcomes) {
                if (outcome.first == i) {
                    EXPECT_EQ(outcome.second, snake.getDirection())
                            << "Failed at step " << i << " with direction change to " << static_cast<int>(directionChanges[i]);
                }
            }
        }
    }


};

#endif//SNAKE_SNAKETESTS_H
