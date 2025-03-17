#include "Graphics.h"
#include "Game.h"
#include "Utils.h"
#include <algorithm>
#include <filesystem>


void Graphics::printHorizontalFence(const Game &game) {
    for (int i{}; i < game.size.first + 2; i++) {// +2 because of the first and the last elements
        bufferScreen << game.symbol;
    }
    bufferScreen << std::endl;
}

void Graphics::printVerticalFenceAndPlayableArea(const Game &game, int j) {
    bufferScreen << game.symbol;
    std::vector<std::pair<int, int>> snakePositions = game.snake.getPositions();
    std::ranges::sort(snakePositions);
    for (int i{}; i < game.size.first; i++) {
        std::pair<int, int> pos = std::make_pair(i, j);
        bool positionSnake = Utils::binarySearch(snakePositions, pos);
        if (positionSnake)
            bufferScreen << game.snake.getSymbol();
        else if (game.food->getPosition() == pos)
            bufferScreen << game.food->getSymbol();
        else if (game.superFood->isEnabled() && game.superFood->getPosition() == pos)
            bufferScreen << game.superFood->getSymbol();
        else
            bufferScreen << " ";
    }
    bufferScreen << game.symbol;
    bufferScreen << std::endl;
}

void Graphics::printToBufferScreen(const Game &game) {
    bufferScreen.clear();
    bufferScreen.str("");
    bufferScreen << "Snake game" << std::endl;
    printHorizontalFence(game);
    for (int j{}; j < game.size.second; j++) {
        printVerticalFenceAndPlayableArea(game, j);
    }
    printHorizontalFence(game);
    bufferScreen << "Score: " << game.score << std::endl;
    if (game.superFood->isEnabled())
        bufferScreen << "Moves left for Super Food: " << game.superFood->getMovesLeft() << std::endl;
    if (game.pause)
        bufferScreen << "Game paused" << std::endl;
}

const std::stringstream &Graphics::getBufferScreen() const {
    return bufferScreen;
}

void Graphics::about() {
    std::cout << "About" << std::endl
              << "2023 Snake game" << std::endl
              << "Developed by Adriano Valadar and Rogério Lopes" << std::endl;
}

void Graphics::showKeysAndSymbols(const Game &game) const {
    std::cout << "Show keys and symbols" << std::endl
              << "Keys:" << std::endl
              << KEY_MOVE_UP << " - Move up" << std::endl
              << KEY_MOVE_DOWN << " - Move down" << std::endl
              << KEY_MOVE_LEFT << " - Move left" << std::endl
              << KEY_MOVE_RIGHT << " - Move right" << std::endl
              << KEY_PAUSE << " - Pause/Resume" << std::endl
              << KEY_SAVE
              << " - Save and go back to menu" << std::endl
              << std::endl
              << "Symbols:" << std::endl
              << game.snake.getSymbol() << " - Snake" << std::endl
              << game.food->getSymbol() << " - Regular food" << std::endl
              << game.superFood->getSymbol() << " - Super food" << std::endl
              << SYMBOL_BORDERS_OFF << " - Borders off" << std::endl
              << SYMBOL_BORDERS_ON << " - Borders on" << std::endl;
}

void Graphics::showMenu(const Game &game) const {
    std::cout << "  _____             _                    " << std::endl
              << " / ____|           | |                                    " << std::endl
              << "| (___  _ __   __ _| | _____    __ _  __ _ _ __ ___   ___ " << std::endl
              << R"( \___ \| '_ \ / _` | |/ / _ \  / _` |/ _` | '_ ` _ \ / _ \ )" << std::endl
              << " ____) | | | | (_| |   <  __/ | (_| | (_| | | | | | |  __/" << std::endl
              << R"(|_____/|_| |_|\__,_|_|\_\___|  \__, |\__,_|_| |_| |_|\___|)" << std::endl
              << "                                __/ |" << std::endl
              << "                               |___/" << std::endl
              << std::endl
              << "Info: map size " << game.size.first << "x" << game.size.second << ", borders " << Utils::Utils::boolToAlpha(game.borders) << std::endl;

    if (std::filesystem::exists(game.directoryName + "/" + game.gameFileName) && !std::filesystem::is_directory(game.directoryName + "/" + game.gameFileName)) {
        std::cout << "0 - Continue game" << std::endl;
    }
    std::cout << "1 - New game" << std::endl
              << "2 - Best scores" << std::endl
              << "3 - Settings" << std::endl
              << "4 - Show keys and symbols" << std::endl
              << "5 - About" << std::endl
              << "9 - Exit" << std::endl
              << "Insert option: ";
}

void Graphics::showSettings(std::ostream &output) {
    output << "Settings" << std::endl;
    output << "If you want to keep a value, insert the same value as the current one" << std::endl;
    output << "Minimum size of map is " << MIN_LENGTH << "x" << MIN_WIDTH << " and maximum size is " << MAX_LENGTH << "x" << MAX_WIDTH << std::endl;
    output << "Default size of map is " << DEFAULT_LENGTH << "X" << DEFAULT_WIDTH << std::endl;
}

void Graphics::confirmNewGame() {
    std::cout << "Warning: there is a game saved and it will be deleted if a new game is started. "
                 "Do you want to proceed? Type 'a' to accept, any other key to refuse ";
}
