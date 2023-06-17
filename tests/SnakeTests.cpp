#include "gtest/gtest.h"
#include "../src/Snake.h"

TEST(Snake, Increase) {
    std::pair<int,int> expected = {-1,-1};
    Snake snake;
    snake.increase();
    EXPECT_EQ(expected, snake.getPositions().back());
}
