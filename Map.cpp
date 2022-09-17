#include "Map.h"
#include <iostream>

void Map::printLine() {
    for (int i {}; i < x ; i++) {
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void Map::printColumns() {
    for(int j {}; j < x ; j++) {
        if (j == 0 || j == x - 1)
            std::cout << symbol;
        else
            std:: cout << " ";
    }
    std::cout << std::endl;
}

void Map::drawMap() {
    std::cout << "Snake game" << std::endl;
    printLine();
    for(int j {}; j < y ; j++)
        printColumns();
    printLine();
}


