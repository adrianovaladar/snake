#include "../src/Game.h"
#include "gtest/gtest.h"

TEST(Game, selfCollision) {
    Game game;
    Snake snake;
    snake.setPositions({{4, 4}, {4, 4}});
    game.setSnake(snake);
    EXPECT_EQ(true, game.isGameOver());
}

TEST(Game, fenceCollisionDown) {
    Game game;
    Snake snake;
    snake.setPositions({{game.getSize().first / 2, game.getSize().second}});
    game.setSnake(snake);
    EXPECT_EQ(true, game.isGameOver());
}

TEST(Game, fenceCollisionUp) {
    Game game;
    Snake snake;
    snake.setPositions({{game.getSize().first / 2, -1}});
    game.setSnake(snake);
    EXPECT_EQ(true, game.isGameOver());
}

TEST(Game, fenceCollisionLEFT) {
    Game game;
    Snake snake;
    snake.setPositions({{-1, game.getSize().first / 2}});
    game.setSnake(snake);
    EXPECT_EQ(true, game.isGameOver());
}

TEST(Game, fenceCollisionRIGTH) {
    Game game;
    Snake snake;
    snake.setPositions({{game.getSize().first, game.getSize().second / 2}});
    game.setSnake(snake);
    EXPECT_EQ(true, game.isGameOver());
}

TEST(Game, isNotGameOver) {
    Game game;
    game.start();
    EXPECT_EQ(false, game.isGameOver());
}

TEST(Game, isEatFoodTrue) {
    Game game;
    Snake snake;
    Food food;
    food.setPosition({5, 5});
    game.setFood(food);
    snake.setPositions({{5, 5}});
    game.setSnake(snake);
    EXPECT_EQ(true, game.isEatFood());
}

TEST(Game, isEatFoodFalse) {
    Game game;
    Snake snake;
    Food food;
    food.setPosition({5, 5});
    game.setFood(food);
    snake.setPositions({{5, 4}});
    game.setSnake(snake);
    EXPECT_EQ(false, game.isEatFood());
}

TEST(Game, isSnakeInMap) {
    Game game;
    game.start();
    Snake snake;
    snake.setPositions(game.getSize());
    for (auto position: snake.getPositions()) {
        EXPECT_EQ(false, (position.first < 0 || position.second < 0 || position.first > game.getSize().first - 1 || position.second > game.getSize().second - 1));
    }
}
