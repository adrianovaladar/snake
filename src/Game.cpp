#include "Game.h"
#include "Input.h"
#include "Logger.h"
#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

void Game::printHorizontalFence() const {
    for (int i{}; i < size.first + 2; i++) {// +2 because of the first and the last elements
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void Game::printVerticalFenceAndPlayableArea(int j) {
    std::cout << symbol;
    std::vector<std::pair<int, int>> snakePositions = snake.getPositions();
    std::sort(snakePositions.begin(), snakePositions.end());
    for (int i{}; i < size.first; i++) {
        std::pair<int, int> pos = std::make_pair(i, j);
        bool positionSnake = std::binary_search(snakePositions.begin(), snakePositions.end(), pos);
        if (positionSnake)
            std::cout << snake.getSymbol();
        else if (food.getPosition() == pos)
            std::cout << food.getSymbol();
        else
            std::cout << " ";
    }
    std::cout << symbol;
    std::cout << std::endl;
}

bool Game::isGameOver() {
    std::vector<std::pair<int, int>> snakePositions = snake.getPositions();
    bool selfCollision = std::count(snakePositions.begin(), snakePositions.end(), snake.getPositions().at(0)) > 1;
    bool fenceCollision{};
    std::pair<int, int> positionHead = snake.getPositions().at(0);
    if (positionHead.first < 0 || positionHead.second < 0 || positionHead.first > size.first - 1 || positionHead.second > size.second - 1) {
        fenceCollision = true;
    }
    return selfCollision || fenceCollision;
}

bool Game::init(int i, int j, char symbolFence, char symbolSnake, char symbolFood) {
    if (i < 10 || j < 5) {
        log("Invalid size", LOGLEVEL::Error);
        return false;
    }
    size = std::make_pair(i, j);
    this->symbol = symbolFence;
    snake.setSymbol(symbolSnake);
    food.setSymbol(symbolFood);
    food.setPosition(std::make_pair(i, j), snake.getPositions());
    bestScores.setNameFile(size);
    Input::enableRawMode();
    log("Map size: " + std::to_string(size.first) + "," + std::to_string(size.second), LOGLEVEL::Info);
    log("Snake head position: " + std::to_string(snake.getPositions().front().first) + "," + std::to_string(snake.getPositions().front().second), LOGLEVEL::Info);
    return true;
}

void Game::readDirectionAndMoveSnake() {
    int c{};
    if (Input::kbHit())
        c = getchar();
    snake.validateDirection(tolower(c));
    snake.move();
}

void Game::logic() {
    std::this_thread::sleep_for(std::chrono::nanoseconds(100000000));
    readDirectionAndMoveSnake();
    if (isEatFood()) {
        snake.increase();
        score++;
        food.setPosition(this->size, snake.getPositions());
    }
    if (isGameOver()) {
        log("Game over, snake head at " + std::to_string(snake.getPositions().front().first) + "," + std::to_string(snake.getPositions().front().second), LOGLEVEL::Info);
        Input::disableRawMode();
        bestScores.read();
        if (bestScores.isBestScore(score)) {
            bestScores.updateAndWrite(std::cin, std::cout, score);
        }
        bestScores.print();
    }
}

void Game::print() {
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Snake game" << std::endl;
    printHorizontalFence();
    for (int j{}; j < this->size.second; j++) {
        printVerticalFenceAndPlayableArea(j);
    }
    printHorizontalFence();
    std::cout << "Score: " << score << std::endl;
}

bool Game::isEatFood() {
    bool isEatFood = snake.getPositions().at(0) == food.getPosition();
    return isEatFood;
}

void Game::setSnake(const Snake &s) {
    Game::snake = s;
}

const std::pair<int, int> &Game::getSize() const {
    return size;
}
void Game::setFood(const Food &f) {
    Game::food = f;
}

Game::~Game() = default;
