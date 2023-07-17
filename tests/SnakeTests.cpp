#include "../src/Snake.h"
#include "gtest/gtest.h"
#include <vector>

TEST(Snake, increase) {
    Snake snake;
    size_t sizeBefore{snake.getPositions().size()};
    ++snake;
    EXPECT_EQ(sizeBefore + 1, snake.getPositions().size());
    // check if the last position is -1, -1
    std::pair<int, int> expectedPosition = {-1, -1};
    EXPECT_EQ(expectedPosition, snake.getPositions().back());
}

TEST(Snake, constructor) {
    Snake snake;
    EXPECT_EQ('o', snake.getSymbol());
    EXPECT_EQ(Direction::RIGHT, snake.getDirection());
    EXPECT_EQ(0, snake.getPositions().size());
}


TEST(Snake, moveRight) {
    Snake snake;
    snake.setPositions({{2, 2}});
    // default direction is right
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.first++;
    snake.move({80, 20}, false);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST(Snake, moveLeft) {
    Snake snake;
    snake.setPositions({{2, 2}});
    snake.setDirection(Direction::LEFT);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.first--;
    snake.move({80, 20}, false);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST(Snake, moveUp) {
    Snake snake;
    snake.setPositions({{2, 2}});
    snake.setDirection(Direction::UP);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.second--;
    snake.move({80, 20}, false);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST(Snake, moveDown) {
    Snake snake;
    snake.setPositions({{2, 2}});
    snake.setDirection(Direction::DOWN);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.second++;
    snake.move({80, 20}, false);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST(Snake, validateRightDirection) {
    Snake snake;
    snake.setPositions({{2, 2}});
    snake.validateDirection(Direction::LEFT);
    EXPECT_EQ(Direction::RIGHT, snake.getDirection());
    snake.validateDirection(Direction::RIGHT);
    EXPECT_EQ(Direction::RIGHT, snake.getDirection());
    snake.validateDirection(Direction::UP);
    EXPECT_EQ(Direction::UP, snake.getDirection());
    snake.validateDirection(Direction::RIGHT);
    snake.validateDirection(Direction::DOWN);
    EXPECT_EQ(Direction::DOWN, snake.getDirection());
}
TEST(Snake, validateLeftDirection) {
    Snake snake;
    snake.setPositions({{2, 2}});
    snake.setDirection(Direction::LEFT);
    snake.validateDirection(Direction::LEFT);
    EXPECT_EQ(Direction::LEFT, snake.getDirection());
    snake.validateDirection(Direction::RIGHT);
    EXPECT_EQ(Direction::LEFT, snake.getDirection());
    snake.validateDirection(Direction::UP);
    EXPECT_EQ(Direction::UP, snake.getDirection());
    snake.validateDirection(Direction::LEFT);
    snake.validateDirection(Direction::DOWN);
    EXPECT_EQ(Direction::DOWN, snake.getDirection());
}
TEST(Snake, validateUpDirection) {
    Snake snake;
    snake.setPositions({{2, 2}});
    snake.setDirection(Direction::UP);
    snake.validateDirection(Direction::LEFT);
    EXPECT_EQ(Direction::LEFT, snake.getDirection());
    snake.validateDirection(Direction::UP);
    snake.validateDirection(Direction::RIGHT);
    EXPECT_EQ(Direction::RIGHT, snake.getDirection());
    snake.validateDirection(Direction::UP);
    EXPECT_EQ(Direction::UP, snake.getDirection());
    snake.validateDirection(Direction::DOWN);
    EXPECT_EQ(Direction::UP, snake.getDirection());
}
TEST(Snake, validateDownDirection) {
    Snake snake;
    snake.setPositions({{2, 2}});
    // test down direction
    snake.setDirection(Direction::DOWN);
    snake.validateDirection(Direction::LEFT);
    EXPECT_EQ(Direction::LEFT, snake.getDirection());
    snake.validateDirection(Direction::DOWN);
    snake.validateDirection(Direction::RIGHT);
    EXPECT_EQ(Direction::RIGHT, snake.getDirection());
    snake.validateDirection(Direction::DOWN);
    snake.validateDirection(Direction::UP);
    EXPECT_EQ(Direction::DOWN, snake.getDirection());
    snake.validateDirection(Direction::DOWN);
    EXPECT_EQ(Direction::DOWN, snake.getDirection());
}
