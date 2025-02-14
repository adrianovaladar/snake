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
    snake.setPositions({{2, 2}});
    // default direction is right
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.first++;
    move({80, 20}, true);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, moveRightBorderOff) {
    snake.setPositions({{79, 5}});
    // default direction is right
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.first = 0;
    move({80, 20}, false);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, moveLeftBorderOn) {
    snake.setPositions({{2, 2}});
    snake.setDirection(Direction::LEFT);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.first--;
    move({80, 20}, true);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, moveLeftBorderOff) {
    snake.setPositions({{0, 2}});
    snake.setDirection(Direction::LEFT);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.first = 79;
    move({80, 20}, false);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, moveUpBorderOn) {
    snake.setPositions({{2, 2}});
    snake.setDirection(Direction::UP);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.second--;
    move({80, 20}, true);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, moveUpBorderOff) {
    snake.setPositions({{2, 0}});
    snake.setDirection(Direction::UP);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.second = 19;
    move({80, 20}, false);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, moveDownBorderOn) {
    snake.setPositions({2,2});
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.second++;
    moveTests(Direction::DOWN, expectedPosition, true);
}

TEST_F(SnakeTests, moveDownBorderOff) {
    snake.setPositions({{2, 19}});
    snake.setDirection(Direction::DOWN);
    auto expectedPosition = snake.getPositions().front();
    expectedPosition.second = 0;
    move({80, 20}, false);
    EXPECT_EQ(expectedPosition, snake.getPositions().front());
}

TEST_F(SnakeTests, validateRightDirection) {
    runDirectionValidationTest(
            Direction::RIGHT,  // Initial direction
            {Direction::LEFT, Direction::RIGHT, Direction::UP, Direction::RIGHT, Direction::DOWN},  // Sequence of changes
            {
                    {0, Direction::RIGHT},  // After 1st change, direction should remain RIGHT
                    {1, Direction::RIGHT},  // After 2nd change, still RIGHT
                    {2, Direction::UP},     // After 3rd change, direction changes to UP
                    {4, Direction::DOWN}    // After 5th change, direction changes to DOWN
            }
    );
}

TEST_F(SnakeTests, validateLeftDirection) {
    runDirectionValidationTest(
            Direction::LEFT,
            {Direction::LEFT, Direction::RIGHT, Direction::UP, Direction::LEFT, Direction::DOWN},
            {
                    {0, Direction::LEFT},
                    {1, Direction::LEFT},
                    {2, Direction::UP},
                    {4, Direction::DOWN}
            }
    );
}

TEST_F(SnakeTests, validateUpDirection) {
    runDirectionValidationTest(
            Direction::UP,
            {Direction::LEFT, Direction::UP, Direction::RIGHT, Direction::UP, Direction::DOWN},
            {
                    {0, Direction::LEFT},
                    {2, Direction::RIGHT},
                    {3, Direction::UP},
                    {4, Direction::UP}
            }
    );
}

TEST_F(SnakeTests, validateDownDirection) {
    runDirectionValidationTest(
            Direction::DOWN,
            {Direction::LEFT, Direction::DOWN, Direction::RIGHT, Direction::DOWN, Direction::UP, Direction::DOWN},
            {
                    {0, Direction::LEFT},
                    {2, Direction::RIGHT},
                    {4, Direction::DOWN},
                    {5, Direction::DOWN}
            }
    );
}
