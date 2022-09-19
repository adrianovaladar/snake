#include "Map.h"
#include <iostream>
#include <vector>
#include<bits/stdc++.h>


void Map::printHorizontalFence() {
    for (int i {}; i < x + 2 ; i++) { // +2 because of the first and the last elements
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void Map::printVerticalFence(int j) {
    std::cout << symbol;
    std::vector<std::pair<int, int>> snakePositions = snake.getPositionsSnake();
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

void Map::drawMap() {
    std::cout << "Snake game" << std::endl;
    printHorizontalFence();
    for(int j {}; j < y ; j++)
        printVerticalFence(j);
    printHorizontalFence();
}


