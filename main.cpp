#include <iostream>
#include "Game.h"

void printHelp() {
    std::cout << "To run this game, please insert no parameters or insert them as following:" << std::endl;
    std::cout << "SizeX SizeY symbolFence symbolSnake symbolFood (still under development)";
    std::cout << std::endl;
}

void printBye() {
    std::cout << "Bye!" << std::endl;
    std::cout << "Game developed by Adriano Valadar and Rogério Lopes" << std::endl;
}

int main (int argc, char *argv[]) {
    if (argc != 1 && argc != 6) {
        printHelp();
    }
    else {
        Game game;
        if (argc == 1)
            game.init(80, 10, '#', 'o', 'f');
        else
            game.init(std::stoi(argv[1]), std::stoi(argv[2]), *argv[3], *argv[4], *argv[5]);
        while(!game.isGameOver()) {
            game.print();
            game.logic();
        }
    }
    printBye();
    return 0;
}