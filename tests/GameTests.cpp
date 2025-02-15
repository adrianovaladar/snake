#include "../src/Game.h"
#include "GameTests.h"
#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>

TEST_F(GameTests, selfCollision) {
    Game game;
    Snake snake;
    snake.setPositions({{4, 4}, {4, 4}});
    game.setSnake(snake);
    EXPECT_EQ(true, game.isGameOver());
}

TEST_F(GameTests, fenceCollisionDown) {
    Game game;
    Snake snake;
    snake.setPositions({{game.getSize().first / 2, game.getSize().second}});
    game.setSnake(snake);
    game.setBorders(true);
    EXPECT_EQ(true, game.isGameOver());
}

TEST_F(GameTests, fenceCollisionUp) {
    Game game;
    Snake snake;
    snake.setPositions({{game.getSize().first / 2, -1}});
    game.setSnake(snake);
    game.setBorders(true);
    EXPECT_EQ(true, game.isGameOver());
}

TEST_F(GameTests, fenceCollisionLeft) {
    Game game;
    Snake snake;
    snake.setPositions({{-1, game.getSize().first / 2}});
    game.setSnake(snake);
    game.setBorders(true);
    EXPECT_EQ(true, game.isGameOver());
}

TEST_F(GameTests, fenceCollisionRight) {
    Game game;
    Snake snake;
    snake.setPositions({{game.getSize().first, game.getSize().second / 2}});
    game.setSnake(snake);
    game.setBorders(true);
    EXPECT_EQ(true, game.isGameOver());
}

TEST_F(GameTests, isNotGameOver) {
    Game game;
    game.start();
    EXPECT_EQ(false, game.isGameOver());
}

TEST_F(GameTests, isEatFoodTrue) {
    Game game;
    Snake snake;
    std::unique_ptr<Food> food = std::make_unique<Food>();
    food->setPosition({5, 5});
    game.setRegularFood(std::move(food));
    snake.setPositions({{5, 5}});
    game.setSnake(snake);
    EXPECT_EQ(true, game.isEatRegularFood());
}

TEST_F(GameTests, isEatFoodFalse) {
    Game game;
    Snake snake;
    std::unique_ptr<Food> food = std::make_unique<Food>();
    food->setPosition({5, 5});
    game.setRegularFood(std::move(food));
    snake.setPositions({{5, 4}});
    game.setSnake(snake);
    EXPECT_EQ(false, game.isEatRegularFood());
}

TEST_F(GameTests, isSnakeInMap) {
    Game game;
    game.start();
    Snake snake;
    snake.setPositions(game.getSize());
    for (auto position: snake.getPositions()) {
        EXPECT_EQ(false, (position.first < 0 || position.second < 0 || position.first > game.getSize().first - 1 || position.second > game.getSize().second - 1));
    }
}

TEST_F(GameTests, writeSettings) {
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

TEST_F(GameTests, readSettings) {
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

TEST_F(GameTests, saveAndLoad) {
    std::string directoryName = "files";
    std::string fileName = "game_80_20_off";
    std::string fileString = directoryName + "/" + fileName;
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    Game game;
    Snake snake;
    std::unique_ptr<Food> food = std::make_unique<Food>();
    food->setPosition({5, 5});
    std::pair<int, int> positionsRegularFood = food->getPosition();
    game.setRegularFood(std::move(food));
    std::unique_ptr<Food> superFood = std::make_unique<SuperFood>();
    dynamic_cast<SuperFood *>(superFood.get())->setEnabled(true);
    superFood->setPosition({5, 5});
    std::pair<int, int> positionsSuperFood = superFood->getPosition();
    game.setSuperFood(std::move(superFood));
    snake.setPositions({{5, 5}});
    validateDirectionSnake(snake, Direction::UP);
    game.setSnake(snake);
    game.setBorders(false);
    game.updateGameFileName();
    game.save();
    Game game2;
    game2.setBorders(false);
    game2.updateGameFileName();
    game2.load();
    std::ifstream file(fileString, std::ios::binary);
    if (!file) {
        EXPECT_EQ(1, game2.getSnake().getPositions().size());
    } else {
        EXPECT_EQ(snake.getPositions(), game2.getSnake().getPositions());
        EXPECT_EQ(Direction::UP, snake.getDirection());
        EXPECT_EQ(positionsRegularFood, game2.getRegularFood().getPosition());
        EXPECT_EQ(positionsSuperFood, game2.getSuperFood().getPosition());
        EXPECT_EQ(true, game2.isEatRegularFood());
        EXPECT_EQ(true, game2.isEatSuperFood());
        EXPECT_EQ(false, game2.hasBorders());
        if (std::filesystem::exists(directoryName) && std::filesystem::is_directory(directoryName)) {
            std::filesystem::remove_all(directoryName);// Remove the empty directory
        }
    }
}
