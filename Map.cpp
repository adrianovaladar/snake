#include "Map.h"
#include <iostream>
#include <vector>

void Map::printHorizontalFence() {
    for (int i {}; i < x + 2 ; i++) { // +2 because of the first and the last elements
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void Map::printVerticalFence(int y) {
    std::cout << symbol;
    std::vector<std::vector<int>> snakePositions = snake.getPositionsSnake();
  //  std::vector <std::vector<int>>::iterator it= snakePositions.begin();
    for(int i {}; i < x ; i++) {
        if (i == snakePositions[i][y]) // fix condition
            std::cout << snake.getSymbol();
        else
            std::cout << " ";
    }
    std::cout << symbol;
    std::cout << std::endl;

}

void Map::drawMap() {
    std::cout << "Snake game" << std::endl;
    printHorizontalFence();
    for(int j {}; j < y ; j++)
        printVerticalFence(j);
    printHorizontalFence();
}


