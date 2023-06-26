#include "Game.h"
#include "Logger.h"
#include <iostream>

void printHelp() {
    std::cout << "To run this game, please insert no parameters or insert them as following:" << std::endl;
    std::cout << "sizeX sizeY symbolFence symbolSnake symbolFood" << std::endl;
    std::cout << "Minimum for sixeX and sixeY is 10 and 5 respectively" << std::endl;
    std::cout << "Default values: 80 20 # o f" << std::endl;
    std::cout << "Keys: w (move up) s (move down) a (move left) d (move right)" << std::endl;
}

void printBye() {
    std::cout << "Bye!" << std::endl;
    std::cout << "Game developed by Adriano Valadar and Rogério Lopes" << std::endl;
}

Logger *Logger::instancePtr = nullptr;

int main(int argc, char *argv[]) {
    Logger *logger = Logger::getInstance();
    logger->log("test", LOGLEVEL::Info);
    if (argc != 1 && argc != 6) {
        printHelp();
    } else {
        Game game{};
        bool isGameOk;
        if (argc == 1)
            isGameOk = game.init(80, 20, '#', 'o', 'f');
        else
            isGameOk = game.init(std::stoi(argv[1]), std::stoi(argv[2]), *argv[3], *argv[4], *argv[5]);
        if (isGameOk) {
            while (!game.isGameOver()) {
                game.print();
                game.logic();
            }
        } else
            printHelp();
    }
    printBye();
    return 0;
}
