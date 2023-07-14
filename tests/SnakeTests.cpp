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
    snake.move();
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST(Snake, moveLeft) {
    Snake snake;
    snake.setPositions({{2, 2}});
    snake.setDirection(Direction::LEFT);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.first--;
    snake.move();
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST(Snake, moveUp) {
    Snake snake;
    snake.setPositions({{2, 2}});
    snake.setDirection(Direction::UP);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.second--;
    snake.move();
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST(Snake, moveDown) {
    Snake snake;
    snake.setPositions({{2, 2}});
    snake.setDirection(Direction::DOWN);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.second++;
    snake.move();
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST(Snake, validateRightDirection) {
    Snake snake;
    snake.setPositions({{2, 2}});
    snake.validateDirection('a');
    EXPECT_EQ(Direction::RIGHT, snake.getDirection());
    snake.validateDirection('d');
    EXPECT_EQ(Direction::RIGHT, snake.getDirection());
    snake.validateDirection('w');
    EXPECT_EQ(Direction::UP, snake.getDirection());
    snake.validateDirection('d');
    snake.validateDirection('s');
    EXPECT_EQ(Direction::DOWN, snake.getDirection());
    // character that does not change direction
    snake.validateDirection('q');
    EXPECT_EQ(Direction::DOWN, snake.getDirection());
}
TEST(Snake, validateLeftDirection) {
    Snake snake;
    snake.setPositions({{2, 2}});
    snake.setDirection(Direction::LEFT);
    snake.validateDirection('a');
    EXPECT_EQ(Direction::LEFT, snake.getDirection());
    snake.validateDirection('d');
    EXPECT_EQ(Direction::LEFT, snake.getDirection());
    snake.validateDirection('w');
    EXPECT_EQ(Direction::UP, snake.getDirection());
    snake.validateDirection('a');
    snake.validateDirection('s');
    EXPECT_EQ(Direction::DOWN, snake.getDirection());
    // character that does not change direction
    snake.validateDirection('q');
    EXPECT_EQ(Direction::DOWN, snake.getDirection());
}
TEST(Snake, validateUpDirection) {
    Snake snake;
    snake.setPositions({{2, 2}});
    snake.setDirection(Direction::UP);
    snake.validateDirection('a');
    EXPECT_EQ(Direction::LEFT, snake.getDirection());
    snake.validateDirection('w');
    snake.validateDirection('d');
    EXPECT_EQ(Direction::RIGHT, snake.getDirection());
    snake.validateDirection('w');
    EXPECT_EQ(Direction::UP, snake.getDirection());
    snake.validateDirection('s');
    EXPECT_EQ(Direction::UP, snake.getDirection());
    // character that does not change direction
    snake.validateDirection('q');
    EXPECT_EQ(Direction::UP, snake.getDirection());
}
TEST(Snake, validateDownDirection) {
    Snake snake;
    snake.setPositions({{2, 2}});
    // test down direction
    snake.setDirection(Direction::DOWN);
    snake.validateDirection('a');
    EXPECT_EQ(Direction::LEFT, snake.getDirection());
    snake.validateDirection('s');
    snake.validateDirection('d');
    EXPECT_EQ(Direction::RIGHT, snake.getDirection());
    snake.validateDirection('s');
    snake.validateDirection('w');
    EXPECT_EQ(Direction::DOWN, snake.getDirection());
    snake.validateDirection('s');
    EXPECT_EQ(Direction::DOWN, snake.getDirection());
    // character that does not change direction
    snake.validateDirection('q');
    EXPECT_EQ(Direction::DOWN, snake.getDirection());
}
