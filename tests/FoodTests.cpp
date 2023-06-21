#include "../src/Food.h"
#include "gtest/gtest.h"

TEST(Food, setPosition) {
    Food food;
    std::pair<int, int> sizeMap = {10, 15};
    std::vector<std::pair<int, int>> positionsSnake;
    positionsSnake.emplace_back(4, 4);
    positionsSnake.emplace_back(3, 4);
    positionsSnake.emplace_back(2, 4);
    std::sort(positionsSnake.begin(), positionsSnake.end());
    bool isSnakePosition;
    for (int i = 0; i < 100; i++) {
        food.setPosition(sizeMap, positionsSnake);
        isSnakePosition = std::binary_search(positionsSnake.begin(), positionsSnake.end(), food.getPosition());
        EXPECT_EQ(false, isSnakePosition);
        EXPECT_LT(food.getPosition().first, sizeMap.first);
        EXPECT_GE(food.getPosition().first, 0);
        EXPECT_LT(food.getPosition().second, sizeMap.second);
        EXPECT_GE(food.getPosition().second, 0);
    }
}
