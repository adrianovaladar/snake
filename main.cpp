#include <iostream>
#include "Game.h"

void printHelp() {
    std::cout << "To run this game, please insert no parameters or insert them as following:" << std::endl;
    std::cout << "SizeX SizeY symbolFence symbolSnake symbolFood (still under development)";
}

void printBye() {
    std::cout << "Bye!" << std::endl;
    std::cout << "Game made by Adriano Valadar and Rogério Lopes" << std::endl;
}

int main (int argc, char *argv[]) {
    if (argc != 1) { //  && argc != 6
        printHelp();
    }
    else {
        Game game(80, 10, '#');
        game.drawMap();
    }
    printBye();
    return 0;
}