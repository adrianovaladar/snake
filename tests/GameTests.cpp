#include "../src/Game.h"
#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>

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

TEST(Game, fenceCollisionLeft) {
    Game game;
    Snake snake;
    snake.setPositions({{-1, game.getSize().first / 2}});
    game.setSnake(snake);
    EXPECT_EQ(true, game.isGameOver());
}

TEST(Game, fenceCollisionRight) {
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

TEST(Game, writeSettings) {
    Game game;
    game.writeSettings();
    std::ifstream file("settings", std::ios::binary);
    if (!file) {
        std::pair<int, int> expectedPair{DEFAULT_LENGTH, DEFAULT_WIDTH};
        EXPECT_EQ(expectedPair, game.getSize());
    } else {
        // Seek to the end of the file
        file.seekg(0, std::ios::end);
        // Get the file size
        std::streampos fileSize = file.tellg();
        // Close the file
        file.close();
        // Determine the size of std::pair<int, int>
        std::size_t pairSize = sizeof(std::pair<int, int>);
        EXPECT_EQ(fileSize, pairSize);
    }
}

TEST(Game, readSettings) {
    Game game;
    game.writeSettings();
    std::string fileNameTest = "test";
    std::ofstream myFile;
    myFile.open(fileNameTest, std::ios::out);
    myFile << "70" << std::endl;
    myFile << "70" << std::endl;
    myFile.close();
    std::ifstream ifs;
    ifs.open(fileNameTest, std::ios::out);
    std::ifstream file;
    file.open(fileNameTest, std::ios::in);
    std::stringstream output;
    if (!file) {
        std::pair<int, int> expectedSize{DEFAULT_LENGTH, DEFAULT_WIDTH};
        EXPECT_EQ(expectedSize, game.getSize());
    } else {
        game.settings(file, output);
        file.close();
        game.readSettings();
        std::pair<int, int> expectedSize = {70, 70};
        EXPECT_EQ(expectedSize, game.getSize());
    }
}

TEST(Game, saveAndLoad) {
    std::string directoryName = "files";
    std::string fileName = "game_80_20";
    std::string fileString = directoryName + "/" + fileName;
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    Game game;
    Snake snake;
    Food food;
    food.setPosition({5, 5});
    game.setFood(food);
    snake.setPositions({{5, 5}});
    snake.validateDirection(Direction::UP);
    game.setSnake(snake);
    game.updateGameFileName();
    game.save();
    Game game2;
    game2.updateGameFileName();
    game2.load();
    std::ifstream file(fileString, std::ios::binary);
    if (!file) {
        EXPECT_EQ(3, game.getSnake().getPositions().size());
    }
    EXPECT_EQ(snake.getPositions(), game2.getSnake().getPositions());
    EXPECT_EQ(Direction::UP, snake.getDirection());
    EXPECT_EQ(food.getPosition(), game2.getFood().getPosition());
    EXPECT_EQ(true, game2.isEatFood());
    if (std::filesystem::exists(directoryName) && std::filesystem::is_directory(directoryName)) {
        std::filesystem::remove_all(directoryName);// Remove the empty directory
    }
}
