#include "Map.h"
#include <iostream>

void Map::printHorizontalFence() {
    for (int i {}; i < x + 2 ; i++) { // +2 because of the first and the last elements
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void Map::printVerticalFence() {
    std::cout << symbol;
    for(int j {}; j < x ; j++)
        std:: cout << " ";
    std::cout << symbol;
    std::cout << std::endl;
}

void Map::drawMap() {
    std::cout << "Snake game" << std::endl;
    printHorizontalFence();
    for(int j {}; j < y ; j++)
        printVerticalFence();
    printHorizontalFence();
}


