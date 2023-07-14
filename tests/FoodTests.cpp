#include "../src/RegularFood.h"
#include "../src/SuperFood.h"
#include "gtest/gtest.h"

TEST(RegularFood, setPosition) {
    std::unique_ptr<Food> regularFood = std::make_unique<RegularFood>();
    std::pair<int, int> sizeMap = {10, 15};
    std::vector<std::pair<int, int>> positionsSnake;
    positionsSnake.emplace_back(4, 4);
    positionsSnake.emplace_back(3, 4);
    positionsSnake.emplace_back(2, 4);
    std::sort(positionsSnake.begin(), positionsSnake.end());
    bool isSnakePosition;
    std::pair<int, int> otherFoodPosition{1, 1};
    for (int i = 0; i < 100; i++) {
        regularFood->setPosition(sizeMap, positionsSnake, otherFoodPosition);
        isSnakePosition = std::binary_search(positionsSnake.begin(), positionsSnake.end(), regularFood->getPosition());
        EXPECT_EQ(false, isSnakePosition);
        EXPECT_NE(regularFood->getPosition(), otherFoodPosition);
        EXPECT_LT(regularFood->getPosition().first, sizeMap.first);
        EXPECT_GE(regularFood->getPosition().first, 0);
        EXPECT_LT(regularFood->getPosition().second, sizeMap.second);
        EXPECT_GE(regularFood->getPosition().second, 0);
    }
}

TEST(SuperFood, setPosition) {
    std::unique_ptr<Food> superFood = std::make_unique<RegularFood>();
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
