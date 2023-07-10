#include "Game.h"
#include "Input.h"
#include "Logger.h"
#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

void clearScreen() {
    // Position cursor in the top-left corner
    std::cout << "\033[1;1H";
    // Clear the screen
    std::cout << "\033[2J";
}

void signalHandler(int signal) {
    clearScreen();
    system("clear");
    Input::disableRawMode();
    exit(signal);
}

void printExitScreen() {
    std::cout << std::endl
              << "Press enter to exit this screen ";
}

void Game::printHorizontalFence() const {
    for (int i{}; i < size.first + 2; i++) {// +2 because of the first and the last elements
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void Game::printVerticalFenceAndPlayableArea(int j) {
    std::cout << symbol;
    std::vector<std::pair<int, int>> snakePositions = snake.getPositions();
    std::sort(snakePositions.begin(), snakePositions.end());
    for (int i{}; i < size.first; i++) {
        std::pair<int, int> pos = std::make_pair(i, j);
        bool positionSnake = std::binary_search(snakePositions.begin(), snakePositions.end(), pos);
        if (positionSnake)
            std::cout << snake.getSymbol();
        else if (food.getPosition() == pos)
            std::cout << food.getSymbol();
        else
            std::cout << " ";
    }
    std::cout << symbol;
    std::cout << std::endl;
}

bool Game::isGameOver() {
    std::vector<std::pair<int, int>> snakePositions = snake.getPositions();
    bool selfCollision = std::count(snakePositions.begin(), snakePositions.end(), snake.getPositions().at(0)) > 1;
    bool fenceCollision{};
    std::pair<int, int> positionHead = snake.getPositions().at(0);
    if (positionHead.first < 0 || positionHead.second < 0 || positionHead.first > size.first - 1 || positionHead.second > size.second - 1) {
        fenceCollision = true;
    }
    return selfCollision || fenceCollision;
}

void Game::start() {
    score = 0;
    snake.setDirection(Direction::RIGHT);
    snake.setPositions(size);
    log("Map size: " + std::to_string(size.first) + "," + std::to_string(size.second), LOGLEVEL::Info);
    log("Snake head position: " + std::to_string(snake.getPositions().front().first) + "," + std::to_string(snake.getPositions().front().second), LOGLEVEL::Info);
    food.setPosition(size, snake.getPositions());
}

bool Game::readDirectionAndMoveSnake() {
    int c{};
    if (Input::kbHit())
        c = getchar();
    if (tolower(c) == KEY_SAVE) {
        return true;
    }
    if (tolower(c) == KEY_PAUSE) {
        pause = !pause;
    }
    if (!pause) {
        Direction d;
        if (tolower(c) == KEY_MOVE_UP)
            d = Direction::UP;
        else if (tolower(c) == KEY_MOVE_LEFT)
            d = Direction::LEFT;
        else if (tolower(c) == KEY_MOVE_DOWN)
            d = Direction::DOWN;
        else if (tolower(c) == KEY_MOVE_RIGHT)
            d = Direction::RIGHT;
        snake.validateDirection(d);
        snake.move();
    }
    return false;
}

bool Game::logic() {
    std::this_thread::sleep_for(std::chrono::nanoseconds(100000000));
    if (readDirectionAndMoveSnake())
        return true;
    if (isEatFood()) {
        snake.increase();
        score++;
        food.setPosition(this->size, snake.getPositions());
    }
    if (isGameOver()) {
        log("Game over, snake head at " + std::to_string(snake.getPositions().front().first) + "," + std::to_string(snake.getPositions().front().second), LOGLEVEL::Info);
        Input::disableRawMode();
        if (bestScores.isBestScore(score)) {
            bestScores.updateAndWrite(std::cin, std::cout, score);
        }
        bestScores.print(size);
    }
    return false;
}

void Game::print() {
    clearScreen();
    std::cout << "Snake game" << std::endl;
    printHorizontalFence();
    for (int j{}; j < this->size.second; j++) {
        printVerticalFenceAndPlayableArea(j);
    }
    printHorizontalFence();
    std::cout << "Score: " << score << std::endl;
    if (pause)
        std::cout << "Game paused" << std::endl;
}

bool Game::isEatFood() {
    bool isEatFood = snake.getPositions().at(0) == food.getPosition();
    return isEatFood;
}

void Game::setSnake(const Snake &s) {
    Game::snake = s;
}

const std::pair<int, int> &Game::getSize() const {
    return size;
}
void Game::setFood(const Food &f) {
    Game::food = f;
}

Game::~Game() = default;

void Game::save() {
    std::ofstream file(directoryName + "/" + gameFileName, std::ios::binary);
    if (!file || !file.good()) {
        log("Error opening file for writing", LOGLEVEL::Warning);
        return;
    }
    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    size_t positionsSize = snake.getPositions().size();
    file.write(reinterpret_cast<const char *>(&positionsSize), sizeof(positionsSize));
    file.write(reinterpret_cast<const char *>(snake.getPositions().data()), static_cast<std::streamsize>(positionsSize * sizeof(std::pair<int, int>)));
    Direction d = snake.getDirection();
    file.write(reinterpret_cast<const char *>(&d), sizeof(d));
    file.write(reinterpret_cast<const char *>(&food.getPosition()), sizeof(food.getPosition()));
    file.write(reinterpret_cast<const char *>(&score), sizeof(score));

    file.close();
    if (!file.good()) {
        log("Error occurred at writing time", LOGLEVEL::Warning);
    }
}

void Game::load() {
    std::ifstream file(directoryName + "/" + gameFileName, std::ios::binary);
    if (!file) {
        log("Error opening file for reading", LOGLEVEL::Warning);
        return;
    }
    std::pair<int, int> sizeMap;
    file.read(reinterpret_cast<char *>(&sizeMap), sizeof(sizeMap));
    if (sizeMap != size) {
        log("Different map size found in the file", LOGLEVEL::Warning);
        return;
    }
    size_t size1;
    file.read(reinterpret_cast<char *>(&size1), sizeof(size1));
    std::vector<std::pair<int, int>> positionsSnake;
    positionsSnake.resize(size1);
    file.read(reinterpret_cast<char *>(positionsSnake.data()), static_cast<std::streamsize>(size1 * sizeof(positionsSnake.begin())));
    snake.setPositions(positionsSnake);
    Direction d;
    file.read(reinterpret_cast<char *>(&d), sizeof(d));
    snake.validateDirection(d);
    std::pair<int, int> positionFood;
    file.read(reinterpret_cast<char *>(&positionFood), sizeof(positionFood));
    food.setPosition(positionFood);
    file.read(reinterpret_cast<char *>(&score), sizeof(score));
    file.close();
}

void Game::removeIfExists() {
    if (std::filesystem::exists(directoryName + "/" + gameFileName)) {
        std::filesystem::remove(directoryName + "/" + gameFileName);
    }
}

void Game::showMenu() const {

    std::cout << std::endl
              << "            _____             _                    " << std::endl
              << "           / ____|           | |                                    " << std::endl
              << "          | (___  _ __   __ _| | _____    __ _  __ _ _ __ ___   ___ " << std::endl
              << R"(           \___ \| '_ \ / _` | |/ / _ \  / _` |/ _` | '_ ` _ \ / _ \ )" << std::endl
              << "           ____) | | | | (_| |   <  __/ | (_| | (_| | | | | | |  __/" << std::endl
              << R"(          |_____/|_| |_|\__,_|_|\_\___|  \__, |\__,_|_| |_| |_|\___|)" << std::endl
              << "                                          __/ |" << std::endl
              << "                                         |___/" << std::endl
              << std::endl
              << "Info: Map size " << size.first << "x" << size.second << std::endl;
    if (std::filesystem::exists(directoryName + "/" + gameFileName) && !std::filesystem::is_directory(directoryName + "/" + gameFileName)) {
        std::cout << "0 - Continue game" << std::endl;
    }
    std::cout << "1 - New game" << std::endl
              << "2 - Best scores" << std::endl
              << "3 - Settings" << std::endl
              << "4 - Show keys" << std::endl
              << "5 - About" << std::endl
              << "9 - Exit" << std::endl
              << "Insert option: ";
}

void Game::settings(std::istream &input, std::ostream &output) {
    output << "Settings" << std::endl;
    output << "If you want to keep a value, insert the same value as the current one" << std::endl;
    output << "Minimum size of map is " << MIN_LENGTH << "x" << MIN_WIDTH << std::endl;
    output << "Default size of map is " << DEFAULT_LENGTH << "X" << DEFAULT_WIDTH << std::endl;
    std::pair<int, int> tmpSize{};
    do {
        output << "Length (current value is " << size.first << "): ";
        input >> tmpSize.first;
        output << "Width (current value is " << size.second << "): ";
        input >> tmpSize.second;
    } while (tmpSize.first < MIN_LENGTH || tmpSize.second < MIN_WIDTH);
    bool changed{};
    if (tmpSize != size)
        changed = true;
    size = tmpSize;
    if (changed) {
        updateBestScores();
    }
    writeSettings();
    updateGameFileName();
}

void Game::updateBestScores() {
    bestScores.setNameFile(size, directoryName);
    bestScores.read();
}

void Game::about() {
    std::cout << "About" << std::endl
              << "2023 Snake game" << std::endl
              << "Developed by Adriano Valadar and Rogério Lopes" << std::endl;
}

void Game::readSettings() {
    std::ifstream file(directoryName + "/" + settingsFileName, std::ios::binary);
    if (!file) {
        log("Error opening file for reading", LOGLEVEL::Warning);
        return;
    }
    file.read(reinterpret_cast<char *>(&size), sizeof(size));
    file.close();
}

void Game::writeSettings() const {
    std::ofstream file(directoryName + "/" + settingsFileName, std::ios::binary);
    if (!file || !file.good()) {
        log("Error opening file for writing", LOGLEVEL::Warning);
        return;
    }
    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    file.close();
    if (!file.good()) {
        log("Error occurred at writing time", LOGLEVEL::Warning);
    }
}

void Game::play() {
    removeIfExists();
    Input::enableRawMode();
    while (!isGameOver()) {
        print();
        if (logic()) {
            save();
            Input::disableRawMode();
            break;
        }
    }
}

void Game::showKeys() const {
    std::cout << "Show keys" << std::endl;
    std::cout << KEY_MOVE_UP << " - Move up" << std::endl;
    std::cout << KEY_MOVE_DOWN << " - Move down" << std::endl;
    std::cout << KEY_MOVE_LEFT << " - Move left" << std::endl;
    std::cout << KEY_MOVE_RIGHT << " - Move right" << std::endl;
    std::cout << KEY_PAUSE << " - Pause/Resume" << std::endl;
    std::cout << KEY_SAVE
              << " - Save and go back to menu" << std::endl;
}

void Game::updateGameFileName() {
    gameFileName = "game_" + std::to_string(size.first) + "_" + std::to_string(size.second);
}

void Game::run() {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTSTP, signalHandler);
    readSettings();
    updateGameFileName();
    updateBestScores();
    char choice;
    do {
        clearScreen();
        showMenu();
        std::cin >> choice;
        switch (choice) {
            case '0': {
                if (std::filesystem::exists(directoryName + "/" + gameFileName) && !std::filesystem::is_directory(directoryName + "/" + gameFileName)) {
                    load();
                    play();
                }
                printExitScreen();
                break;
            }
            case '1': {
                if (std::filesystem::exists(directoryName + "/" + gameFileName) && !std::filesystem::is_directory(directoryName + "/" + gameFileName)) {
                    char option;
                    std::cout << "Warning: there is a game saved and it will be deleted if a new game is started. Do you want to proceed? Type a to accept, any other key to refuse ";
                    std::cin >> option;
                    if (option != 'a') {
                        printExitScreen();
                        break;
                    }
                }
                start();
                play();
                printExitScreen();
                break;
            }
            case '2': {
                bestScores.print(size);
                printExitScreen();
                break;
            }
            case '3': {
                settings(std::cin, std::cout);
                printExitScreen();
                break;
            }
            case '4': {
                showKeys();
                printExitScreen();
                break;
            }
            case '5': {
                about();
                printExitScreen();
                break;
            }
            default: {
                break;
            }
        }
        if (choice == '0' || choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    } while (choice != '9');
    clearScreen();
    system("clear");
}

int Game::getScore() const {
    return score;
}

const Snake &Game::getSnake() const {
    return snake;
}

const Food &Game::getFood() const {
    return food;
}
