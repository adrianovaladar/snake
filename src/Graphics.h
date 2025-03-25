#ifndef SNAKE_GRAPHICS_H
#define SNAKE_GRAPHICS_H

#include <sstream>

class Game;// Forward declaration of Game class

class Graphics {
    std::stringstream bufferScreen;
    void printVerticalFenceAndPlayableArea(const Game &game, int y);
    void printHorizontalFence(const Game &game);

public:
    void printToBufferScreen(const Game &game);
    const std::stringstream &getBufferScreen() const;
    static void about();
    static void showKeysAndSymbols(const Game &game);
    static void showMenu(const Game &game);
    static void showSettings(std::ostream &output);
};


#endif//SNAKE_GRAPHICS_H
