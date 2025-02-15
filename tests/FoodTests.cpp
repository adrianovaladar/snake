#include "../src/Food.h"
#include "../src/SuperFood.h"
#include "gtest/gtest.h"

TEST(Food, setPosition) {
    std::unique_ptr<Food> food = std::make_unique<Food>();
    std::pair<int, int> sizeMap = {10, 15};
    std::vector<std::pair<int, int>> positionsSnake;
    positionsSnake.emplace_back(4, 4);
    positionsSnake.emplace_back(3, 4);
    positionsSnake.emplace_back(2, 4);
    std::sort(positionsSnake.begin(), positionsSnake.end());
    bool isSnakePosition;
    std::pair<int, int> otherFoodPosition{1, 1};
    for (int i = 0; i < 100; i++) {
        food->setPosition(sizeMap, positionsSnake, otherFoodPosition);
        isSnakePosition = std::binary_search(positionsSnake.begin(), positionsSnake.end(), food->getPosition());
        EXPECT_EQ(false, isSnakePosition);
        EXPECT_NE(food->getPosition(), otherFoodPosition);
        EXPECT_LT(food->getPosition().first, sizeMap.first);
        EXPECT_GE(food->getPosition().first, 0);
        EXPECT_LT(food->getPosition().second, sizeMap.second);
        EXPECT_GE(food->getPosition().second, 0);
    }
}

TEST(SuperFood, setPosition) {
    std::unique_ptr<Food> superFood = std::make_unique<SuperFood>();
    std::pair<int, int> sizeMap = {10, 15};
    std::vector<std::pair<int, int>> positionsSnake;
    positionsSnake.emplace_back(4, 4);
    positionsSnake.emplace_back(3, 4);
    positionsSnake.emplace_back(2, 4);
    std::sort(positionsSnake.begin(), positionsSnake.end());
    bool isSnakePosition;
    std::pair<int, int> otherFoodPosition{1, 1};
    for (int i = 0; i < 100; i++) {
        superFood->setPosition(sizeMap, positionsSnake, otherFoodPosition);
        isSnakePosition = std::binary_search(positionsSnake.begin(), positionsSnake.end(), superFood->getPosition());
        EXPECT_EQ(false, isSnakePosition);
        EXPECT_NE(superFood->getPosition(), otherFoodPosition);
        EXPECT_LT(superFood->getPosition().first, sizeMap.first);
        EXPECT_GE(superFood->getPosition().first, 0);
        EXPECT_LT(superFood->getPosition().second, sizeMap.second);
        EXPECT_GE(superFood->getPosition().second, 0);
    }
}
