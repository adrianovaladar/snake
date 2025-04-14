#include "../src/Game.h"
#include "GameTests.h"
#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>

TEST_F(GameTests, selfCollision) {
    snake.setPositions({{4, 4}, {4, 4}});
    game.setSnake(snake);
    EXPECT_EQ(true, isGameOver());
}

TEST_F(GameTests, fenceCollisionDown) {
    snake.setPositions({{game.getSize().first / 2, game.getSize().second}});
    game.setSnake(snake);
    game.setBorders(true);
    EXPECT_EQ(true, isGameOver());
}

TEST_F(GameTests, fenceCollisionUp) {
    snake.setPositions({{game.getSize().first / 2, -1}});
    game.setSnake(snake);
    game.setBorders(true);
    EXPECT_EQ(true, isGameOver());
}

TEST_F(GameTests, fenceCollisionLeft) {
    snake.setPositions({{-1, game.getSize().first / 2}});
    game.setSnake(snake);
    game.setBorders(true);
    EXPECT_EQ(true, isGameOver());
}

TEST_F(GameTests, fenceCollisionRight) {
    snake.setPositions({{game.getSize().first, game.getSize().second / 2}});
    game.setSnake(snake);
    game.setBorders(true);
    EXPECT_EQ(true, isGameOver());
}

TEST_F(GameTests, isNotGameOver) {
    start();
    EXPECT_EQ(false, isGameOver());
}

TEST_F(GameTests, isFoodEatenTrue) {
    auto food = std::make_unique<Food>();
    food->setPosition({5, 5});
    game.setRegularFood(std::move(food));
    snake.setPositions({{5, 5}});
    game.setSnake(snake);
    EXPECT_EQ(true, isRegularFoodEaten());
}

TEST_F(GameTests, isFoodEatenFalse) {
    auto food = std::make_unique<Food>();
    food->setPosition({5, 5});
    game.setRegularFood(std::move(food));
    snake.setPositions({{5, 4}});
    game.setSnake(snake);
    EXPECT_EQ(false, isRegularFoodEaten());
}

TEST_F(GameTests, isSnakeInMap) {
    start();
    snake.setPositions(game.getSize());
    for (auto [snakePositionX, snakePositionY]: snake.getPositions()) {
        EXPECT_EQ(false, (snakePositionX < 0 || snakePositionY < 0 || snakePositionX > game.getSize().first - 1 || snakePositionY > game.getSize().second - 1));
    }
}

TEST_F(GameTests, writeSettings) {
    writeSettings();
    if (std::ifstream file("settings", std::ios::binary); !file) {
        std::pair expectedPair{defaultLength, defaultWidth};
        EXPECT_EQ(expectedPair, game.getSize());
    } else {
        file.seekg(0, std::ios::end);
        std::streampos fileSize = file.tellg();
        file.close();
        std::size_t pairSize = sizeof(std::pair<int, int>);
        EXPECT_EQ(fileSize, pairSize);
    }
}

TEST_F(GameTests, readSettings) {
    writeSettings();
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
    if (!file) {
        std::pair expectedSize{defaultLength, defaultWidth};
        EXPECT_EQ(expectedSize, game.getSize());
    } else {
        std::stringstream output;
        settings(file, output);
        file.close();
        readSettings();
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
    auto food = std::make_unique<Food>();
    food->setPosition({5, 5});
    std::pair<int, int> positionsRegularFood = food->getPosition();
    game.setRegularFood(std::move(food));
    auto superFood = std::make_shared<SuperFood>();
    superFood->setEnabled(true);
    superFood->Food::setPosition({5, 5});
    std::pair<int, int> positionsSuperFood = superFood->getPosition();
    game.setSuperFood(superFood);
    snake.setPositions({{5, 5}});
    validateDirectionSnake(snake, Direction::UP);
    game.setSnake(snake);
    game.setBorders(false);
    updateGameFileName();
    save();
    game2.setBorders(false);
    updateGameFileName2();
    load2();
    if (std::ifstream file(fileString, std::ios::binary); !file) {
        EXPECT_EQ(1, game2.getSnake().getPositions().size());
    } else {
        EXPECT_EQ(snake.getPositions(), game2.getSnake().getPositions());
        EXPECT_EQ(Direction::UP, snake.getDirection());
        EXPECT_EQ(positionsRegularFood, game2.getRegularFood().getPosition());
        EXPECT_EQ(positionsSuperFood, game2.getSuperFood().getPosition());
        EXPECT_EQ(true, isRegularFoodEaten2());
        EXPECT_EQ(true, isSuperFoodEaten2());
        EXPECT_EQ(false, hasBorders2());
        if (std::filesystem::exists(directoryName) && std::filesystem::is_directory(directoryName)) {
            std::filesystem::remove_all(directoryName);// Remove the empty directory
        }
    }
}

TEST_F(GameTests, readSaveKey) {
    ASSERT_EQ(readKey(true, 'm'), true);
}

TEST_F(GameTests, readPauseKey) {
    ASSERT_EQ(readKey(true, 'p'), false);
    ASSERT_EQ(game.getPause(), true);
}
