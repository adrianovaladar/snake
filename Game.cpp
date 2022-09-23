#include "Game.h"
#include <iostream>
#include <vector>
#include<bits/stdc++.h>
#include <chrono>
#include "input.h"


void Game::printHorizontalFence() {
    for (int i {}; i < x + 2 ; i++) { // +2 because of the first and the last elements
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void Game::printVerticalFenceAndPlayableArea(int j) {
    std::cout << symbol;
    std::vector<std::pair<int, int>> snakePositions = snake.getPositions();
    std::sort(snakePositions.begin(), snakePositions.end());
    for(int i {}; i < x ; i++) {
        std::pair<int, int> pos = std::make_pair(i, j);
        bool positionSnake = std::binary_search(snakePositions.begin(), snakePositions.end(), pos);
        if (positionSnake)
            std::cout << snake.getSymbol();
        else
            std::cout << " ";
    }
    std::cout << symbol;
    std::cout << std::endl;

}

void Game::init(int i, int j, char symbolFence, char symbolSnake, char symbolFood) {
    this->x = i;
    this->y = j;
    this->symbol = symbolFence;
    snake.setSymbol(symbolSnake);
    //food.setSymbol(symbolFood);
}

void Game::printMap() {
    bool gameOver = false;
    char c = 'r';
    while(!gameOver) {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "Snake game" << std::endl;
        printHorizontalFence();
        for (int j{}; j < y; j++) {
            printVerticalFenceAndPlayableArea(j);
        }
        printHorizontalFence();
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));
           if(_kbhit())
               c = getchar();
        snake.move(c);
    }
}


