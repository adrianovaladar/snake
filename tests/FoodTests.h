#ifndef SNAKE_FOODTESTS_H
#define SNAKE_FOODTESTS_H

#include "../src/Game.h"
#include <gtest/gtest.h>
#include <algorithm>

class FoodTests : public ::testing::Test {
protected:
    Food food;
    SuperFood superFood;
    std::pair<int, int> sizeMap;
    std::vector<std::pair<int, int>> positionsSnake;
    std::pair<int, int> otherFoodPosition;
    void SetUp() override {
        sizeMap = {10, 15};
        otherFoodPosition = {1, 1};
        positionsSnake.emplace_back(4, 4);
        positionsSnake.emplace_back(3, 4);
        positionsSnake.emplace_back(2, 4);
    }

    void TearDown() override {
    }

    void testSetPosition(Food &food) {
        std::ranges::sort(positionsSnake);
        for (int i = 0; i < 100; i++) {
            food.setPosition(sizeMap, positionsSnake, otherFoodPosition);
            bool isSnakePosition = std::ranges::binary_search(positionsSnake, food.getPosition());
            EXPECT_EQ(false, isSnakePosition);
            EXPECT_NE(food.getPosition(), otherFoodPosition);
            EXPECT_LT(food.getPosition().first, sizeMap.first);
            EXPECT_GE(food.getPosition().first, -1);
            EXPECT_LT(food.getPosition().second, sizeMap.second);
            EXPECT_GE(food.getPosition().second, -1);
        }
    }
};

#endif//SNAKE_FOODTESTS_H
