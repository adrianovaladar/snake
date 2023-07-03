#include "Game.h"
#include "Input.h"
#include "Logger.h"
#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#define MIN_WEIGHT 10
#define MIN_HEIGHT 5

void clearScreen() {
    // Position cursor in the top-left corner
    std::cout << "\033[1;1H";
    // Clear the screen
    std::cout << "\033[2J";
}

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

void Game::start() {
    score = 0;
    snake.setDirection(Direction::RIGHT);
    snake.setPositions(size);
    log("Map size: " + std::to_string(size.first) + "," + std::to_string(size.second), LOGLEVEL::Info);
    log("Snake head position: " + std::to_string(snake.getPositions().front().first) + "," + std::to_string(snake.getPositions().front().second), LOGLEVEL::Info);
    food.setPosition(size, snake.getPositions());
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
        if (bestScores.isBestScore(score)) {
            bestScores.updateAndWrite(std::cin, std::cout, score);
        }
        bestScores.print(size);
    }
}

void Game::print() {
    clearScreen();
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

void Game::showMenu() {

    std::cout << std::endl
              << "            _____             _                    " << std::endl
              << "           / ____|           | |                                    " << std::endl
              << "          | (___  _ __   __ _| | _____    __ _  __ _ _ __ ___   ___ " << std::endl
              << R"(           \___ \| '_ \ / _` | |/ / _ \  / _` |/ _` | '_ ` _ \ / _ \ )" << std::endl
              << "           ____) | | | | (_| |   <  __/ | (_| | (_| | | | | | |  __/" << std::endl
              << R"(          |_____/|_| |_|\__,_|_|\_\___|  \__, |\__,_|_| |_| |_|\___|)" << std::endl
              << "                                          __/ |" << std::endl
              << "                                         |___/" << std::endl
              << std::endl
              << "1 - New game" << std::endl
              << "2 - Best scores" << std::endl
              << "3 - Settings" << std::endl
              << "4 - About" << std::endl
              << "9 - Exit" << std::endl
              << "Insert option: ";
}

void Game::settings() {
    std::cout << "Settings" << std::endl;
    std::cout << "If you want to keep a value, just insert the same value as the current one" << std::endl;
    std::cout << "Minimum size of map is " << MIN_WEIGHT << "x" << MIN_HEIGHT << std::endl;
    std::pair<int, int> tmpSize{};
    do {
        std::cout << "Width (current value is " << size.first << "): ";
        std::cin >> tmpSize.first;
        std::cout << "Height (current value is " << size.second << "): ";
        std::cin >> tmpSize.second;
    } while (tmpSize.first < MIN_WEIGHT || tmpSize.second < MIN_HEIGHT);
    bool read;
    if (tmpSize != size)
        read = true;
    size = tmpSize;
    if (read) {
        bestScores.setNameFile(size);
        bestScores.read();
    }
}

void Game::about() {
    std::cout << "About" << std::endl
              << "2023 Snake game" << std::endl
              << "Developed by Adriano Valadar and Rogério Lopes" << std::endl;
}

void Game::run() {
    char choice;
    bestScores.setNameFile(size);
    bestScores.read();
    do {
        clearScreen();
        showMenu();
        std::cin >> choice;
        switch (choice) {
            case '1': {
                Input::enableRawMode();
                start();
                while (!isGameOver()) {
                    print();
                    logic();
                }
                break;
            }
            case '2': {
                bestScores.print(size);
                break;
            }
            case '3': {
                settings();
                break;
            }
            case '4': {
                about();
                break;
            }
            default: {
                break;
            }
        }
        if (choice == '1' || choice == '2' || choice == '3' || choice == '4') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    } while (choice != '9');
    std::cout << "Bye!" << std::endl;
}
