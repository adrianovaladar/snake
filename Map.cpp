#include "Map.h"
#include <iostream>
#include <vector>
#include<bits/stdc++.h>
#include <chrono>
#include <thread>
#include <termios.h>


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

/* http://www.flipcode.com/archives/_kbhit_for_Linux.shtml */
int morePortable() {
    struct timeval timeout;
    fd_set rdset;

    FD_ZERO(&rdset);
    FD_SET(STDIN_FILENO, &rdset);
    timeout.tv_sec  = 0;
    timeout.tv_usec = 0;

    return select(STDOUT_FILENO, &rdset, NULL, NULL, &timeout);
}

int _kbhit(void) {
    static int initialized = 0;

    if (! initialized) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = 1;
    }

#if 0
    int bytesWaiting;
    ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
    return bytesWaiting;
#else
    return morePortable();
#endif
}

void Map::drawMap() {
    bool gameOver = false;
    char c = 'r';
    while(!gameOver) {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "Snake game" << std::endl;
        printHorizontalFence();
        for (int j{}; j < y; j++) {
            printVerticalFence(j);
        }
        printHorizontalFence();
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));
           if(_kbhit())
               c = getchar();
        snake.move(c);
    }
}


