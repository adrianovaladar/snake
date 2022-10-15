#include "Game.h"
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <chrono>
#include "input.h"
#include "direction.h"

void Game::printHorizontalFence() {
    for (int i {}; i < size.first + 2 ; i++) { // +2 because of the first and the last elements
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void Game::printVerticalFenceAndPlayableArea(int j) {
    std::cout << symbol;
    std::vector<std::pair<int, int>> snakePositions = snake.getPositions();
    std::sort(snakePositions.begin(), snakePositions.end());
    for(int i {}; i < size.first ; i++) {
        std::pair<int, int> pos = std::make_pair(i, j);
        bool positionSnake = std::binary_search(snakePositions.begin(), snakePositions.end(), pos);
        if (positionSnake)
            std::cout << snake.getSymbol();
        else if (food.getPosition()==pos)
            std::cout << food.getSymbol();
        else
            std::cout << " ";
    }
    std::cout << symbol;
    std::cout << std::endl;

}

bool Game::isGameOver() {
    std::vector<std::pair<int, int>> snakePositions = snake.getPositions();
    bool selfCollision {};
    selfCollision = std::count(snakePositions.begin(), snakePositions.end(), snake.getPositions().at(0)) > 1 ? true : false;
    bool fenceCollision {};
    std::pair<int ,int> positionHead = snake.getPositions().at(0);
    if (positionHead.first < 0 || positionHead.second < 0 || positionHead.first > size.first - 1 || positionHead.second > size.second - 1) {
        fenceCollision = true;
    }
    return selfCollision || fenceCollision;
}

bool Game::init(int i, int j, char symbolFence, char symbolSnake, char symbolFood) {
    if (i < 10 || j < 5)
        return false;
    size = std::make_pair(i, j);
    this->symbol = symbolFence;
    snake.setSymbol(symbolSnake);
    food.setSymbol(symbolFood);
    food.setPosition(std::make_pair(i, j), snake.getPositions());
    bestScores.setNameFile(size);
    return true;
}

void Game::readDirectionAndMoveSnake() {
    char c {};
    if(_kbhit())
        c = getchar();
    switch (tolower(c)) {
        case 'w': {
            if (snake.getDirection() != Direction::DOWN)
                snake.setDirection(Direction::UP);
            break;
        }
        case 'a': {
            if (snake.getDirection() != Direction::RIGHT)
                snake.setDirection(Direction::LEFT);
            break;
        }
        case 's': {
            if (snake.getDirection() != Direction::UP)
                snake.setDirection(Direction::DOWN);
            break;
        }
        case 'd': {
            if (snake.getDirection() != Direction::LEFT)
                snake.setDirection(Direction::RIGHT);
            break;
        }
        default: {
            break;
        }
    }
    snake.move();
};

void Game::logic() {
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));
    readDirectionAndMoveSnake();
    if (isEatFood()) {
        snake.increase();
        score++;
        food.setPosition(this->size, snake.getPositions());
    }
    if (isGameOver()) {
        bestScores.read();
        if (bestScores.isBestScore(score) ) {
            bestScores.updateAndWrite(score);
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

Game::~Game() {

}

