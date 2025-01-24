#include "../src/Snake.h"
#include "gtest/gtest.h"
#include <vector>
#include "SnakeTests.h"

TEST_F(SnakeTests, increase) {
    size_t sizeBefore{snake.getPositions().size()};
    ++snake;
    EXPECT_EQ(sizeBefore + 1, snake.getPositions().size());
    // check if the last position is -1, -1
    std::pair<int, int> expectedPosition = {-1, -1};
    EXPECT_EQ(expectedPosition, snake.getPositions().back());
}

TEST_F(SnakeTests, constructor) {
    EXPECT_EQ('o', snake.getSymbol());
    EXPECT_EQ(Direction::RIGHT, snake.getDirection());
    EXPECT_EQ(0, snake.getPositions().size());
}


TEST_F(SnakeTests, moveRightBorderOn) {
    setPositions({{2, 2}});
    // default direction is right
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.first++;
    snake.move({80, 20}, true);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, moveRightBorderOff) {
    setPositions({{79, 5}});
    // default direction is right
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.first = 0;
    snake.move({80, 20}, false);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, moveLeftBorderOn) {
    setPositions({{2, 2}});
    snake.setDirection(Direction::LEFT);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.first--;
    snake.move({80, 20}, true);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, moveLeftBorderOff) {
    setPositions({{0, 2}});
    snake.setDirection(Direction::LEFT);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.first = 79;
    snake.move({80, 20}, false);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, moveUpBorderOn) {
    setPositions({{2, 2}});
    snake.setDirection(Direction::UP);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.second--;
    snake.move({80, 20}, true);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, moveUpBorderOff) {
    setPositions({{2, 0}});
    snake.setDirection(Direction::UP);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.second = 19;
    snake.move({80, 20}, false);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, moveDownBorderOn) {
    setPositions({{2, 2}});
    snake.setDirection(Direction::DOWN);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.second++;
    snake.move({80, 20}, true);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, moveDownBorderOff) {
    setPositions({{2, 19}});
    snake.setDirection(Direction::DOWN);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.second = 0;
    snake.move({80, 20}, false);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, validateRightDirection) {
    setPositions({{2, 2}});
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

TEST_F(SnakeTests, validateLeftDirection) {
    setPositions({{2, 2}});
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
TEST_F(SnakeTests, validateUpDirection) {
    setPositions({{2, 2}});
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
TEST_F(SnakeTests, validateDownDirection) {    
    setPositions({{2, 2}});
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
