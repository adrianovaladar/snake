#include "../src/RegularFood.h"
#include "gtest/gtest.h"

TEST(Food, setPosition) {
    std::unique_ptr<Food> regularFood = std::make_unique<RegularFood>();
    std::pair<int, int> sizeMap = {10, 15};
    std::vector<std::pair<int, int>> positionsSnake;
    positionsSnake.emplace_back(4, 4);
    positionsSnake.emplace_back(3, 4);
    positionsSnake.emplace_back(2, 4);
    std::sort(positionsSnake.begin(), positionsSnake.end());
    bool isSnakePosition;
    for (int i = 0; i < 100; i++) {
        regularFood->setPosition(sizeMap, positionsSnake);
        isSnakePosition = std::binary_search(positionsSnake.begin(), positionsSnake.end(), regularFood->getPosition());
        EXPECT_EQ(false, isSnakePosition);
        EXPECT_LT(regularFood->getPosition().first, sizeMap.first);
        EXPECT_GE(regularFood->getPosition().first, 0);
        EXPECT_LT(regularFood->getPosition().second, sizeMap.second);
        EXPECT_GE(regularFood->getPosition().second, 0);
    }
}
