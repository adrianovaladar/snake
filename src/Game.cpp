#include "Game.h"
#include "Input.h"
#include "Logger.h"
#include "Utils.h"
#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

Game::Game() : size(DEFAULT_LENGTH, DEFAULT_WIDTH), symbol(SYMBOL_BORDERS_ON), score(0), settingsFileName("settings"), directoryName("files"), pause(false), borders(true), foodsEaten(0), velocity(100000000) {
    regularFood = std::make_unique<RegularFood>();
    superFood = std::make_unique<SuperFood>();
}

void Game::printHorizontalFence() {
    for (int i{}; i < size.first + 2; i++) {// +2 because of the first and the last elements
        bufferScreen << symbol;
    }
    bufferScreen << std::endl;
}

void Game::printVerticalFenceAndPlayableArea(int j) {
    bufferScreen << symbol;
    std::vector<std::pair<int, int>> snakePositions = snake.getPositions();
    std::sort(snakePositions.begin(), snakePositions.end());
    for (int i{}; i < size.first; i++) {
        std::pair<int, int> pos = std::make_pair(i, j);
        bool positionSnake = std::binary_search(snakePositions.begin(), snakePositions.end(), pos);
        if (positionSnake)
            bufferScreen << snake.getSymbol();
        else if (regularFood->getPosition() == pos)
            bufferScreen << regularFood->getSymbol();
        else if (dynamic_cast<SuperFood *>(superFood.get())->isEnabled() && superFood->getPosition() == pos)
            bufferScreen << superFood->getSymbol();
        else
            bufferScreen << " ";
    }
    bufferScreen << symbol;
    bufferScreen << std::endl;
}

bool Game::isGameOver() {
    if (score == std::numeric_limits<int>::max())
        return true;
    std::vector<std::pair<int, int>> snakePositions = snake.getPositions();
    bool selfCollision = std::count(snakePositions.begin(), snakePositions.end(), snake.getPositions().at(0)) > 1;
    bool borderCollision{};
    std::pair<int, int> positionHead = snake.getPositions().at(0);
    if (borders && (positionHead.first < 0 || positionHead.second < 0 || positionHead.first > size.first - 1 || positionHead.second > size.second - 1))
        borderCollision = true;
    return selfCollision || borderCollision;
}

void Game::start() {
    score = 0;
    foodsEaten = 0;
    velocity = 100000000;
    snake.setDirection(Direction::RIGHT);
    snake.setPositions(size);
    log("Map size: " + std::to_string(size.first) + "," + std::to_string(size.second), LOGLEVEL::Info);
    log("Snake head position: " + std::to_string(snake.getPositions().front().first) + "," + std::to_string(snake.getPositions().front().second), LOGLEVEL::Info);
    regularFood->setPosition(size, snake.getPositions(), superFood->getPosition());
    dynamic_cast<SuperFood *>(superFood.get())->setEnabled(false);
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
        Direction d = Direction::NONE;
        if (tolower(c) == KEY_MOVE_UP)
            d = Direction::UP;
        else if (tolower(c) == KEY_MOVE_LEFT)
            d = Direction::LEFT;
        else if (tolower(c) == KEY_MOVE_DOWN)
            d = Direction::DOWN;
        else if (tolower(c) == KEY_MOVE_RIGHT)
            d = Direction::RIGHT;
        snake.validateDirection(d);
        snake.move(size, borders);
        if (dynamic_cast<SuperFood *>(superFood.get())->isEnabled()) {
            dynamic_cast<SuperFood *>(superFood.get())->decreaseMovesLeft();
        }
    }
    return false;
}

bool Game::logic() {
    if (readDirectionAndMoveSnake())
        return true;
    if (isEatRegularFood()) {
        ++snake;
        score++;
        foodsEaten++;
        changeVelocity();
        regularFood->setPosition(this->size, snake.getPositions(), superFood->getPosition());
        if (!dynamic_cast<SuperFood *>(superFood.get())->isEnabled()) {
            superFood->setPosition(size, snake.getPositions(), regularFood->getPosition());
            if (dynamic_cast<SuperFood *>(superFood.get())->isEnabled()) {
                int biggerSide = size.first > size.second ? size.first : size.second;
                dynamic_cast<SuperFood *>(superFood.get())->setMovesLeft(static_cast<int>(static_cast<float>(biggerSide) * 0.7f));
            }
        }
    }
    if (isEatSuperFood()) {
        ++snake;
        score += 3;
        foodsEaten++;
        changeVelocity();
        dynamic_cast<SuperFood *>(superFood.get())->setEnabled(false);
        superFood->setPosition({-1, -1});
    }
    if (isGameOver()) {
        log("Game over, snake head at " + std::to_string(snake.getPositions().front().first) + "," + std::to_string(snake.getPositions().front().second), LOGLEVEL::Info);
        Input::disableRawMode();
        if (bestScores.isBestScore(score)) {
            bestScores.updateAndWrite(std::cin, std::cout, score);
        }
        bestScores.print(size, borders);
    }
    return false;
}

void Game::printToBufferScreen() {
    bufferScreen.clear();
    bufferScreen.str("");
    bufferScreen << "Snake game" << std::endl;
    printHorizontalFence();
    for (int j{}; j < this->size.second; j++) {
        printVerticalFenceAndPlayableArea(j);
    }
    printHorizontalFence();
    bufferScreen << "Score: " << score << std::endl;
    if (dynamic_cast<SuperFood *>(superFood.get())->isEnabled())
        bufferScreen << "Moves left for Super Food: " << dynamic_cast<SuperFood *>(superFood.get())->getMovesLeft() << std::endl;
    if (pause)
        bufferScreen << "Game paused" << std::endl;
}

bool Game::isEatRegularFood() {
    bool isEatFood = snake.getPositions().at(0) == regularFood->getPosition();
    return isEatFood;
}

bool Game::isEatSuperFood() {
    return dynamic_cast<SuperFood *>(superFood.get())->isEnabled() && snake.getPositions().at(0) == superFood->getPosition();
}

void Game::setSnake(const Snake &s) {
    Game::snake = s;
}

const std::pair<int, int> &Game::getSize() const {
    return size;
}
void Game::setRegularFood(std::unique_ptr<Food> f) {
    regularFood = std::move(f);
}

void Game::setSuperFood(std::unique_ptr<Food> f) {
    superFood = std::move(f);
}

Game::~Game() = default;

void Game::save() {
    std::ofstream file(directoryName + "/" + gameFileName, std::ios::binary);
    if (!file || !file.good()) {
        log("Error opening file for writing", LOGLEVEL::Warning);
        return;
    }
    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    file.write(reinterpret_cast<const char *>(&borders), sizeof(borders));
    size_t positionsSize = snake.getPositions().size();
    file.write(reinterpret_cast<const char *>(&positionsSize), sizeof(positionsSize));
    file.write(reinterpret_cast<const char *>(snake.getPositions().data()), static_cast<std::streamsize>(positionsSize * sizeof(std::pair<int, int>)));
    Direction d = snake.getDirection();
    file.write(reinterpret_cast<const char *>(&d), sizeof(d));
    file.write(reinterpret_cast<const char *>(&regularFood->getPosition()), sizeof(regularFood->getPosition()));
    file.write(reinterpret_cast<const char *>(&superFood->getPosition()), sizeof(superFood->getPosition()));
    bool enabled = dynamic_cast<SuperFood *>(superFood.get())->isEnabled();
    file.write(reinterpret_cast<const char *>(&enabled), sizeof(enabled));
    int movesLeft = dynamic_cast<SuperFood *>(superFood.get())->getMovesLeft();
    file.write(reinterpret_cast<const char *>(&movesLeft), sizeof(movesLeft));
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
    bool b;
    file.read(reinterpret_cast<char *>(&b), sizeof(b));
    if (b != borders) {
        log("Different border status found in the file", LOGLEVEL::Warning);
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
    std::pair<int, int> positionRegularFood;
    file.read(reinterpret_cast<char *>(&positionRegularFood), sizeof(positionRegularFood));
    regularFood->setPosition(positionRegularFood);
    std::pair<int, int> positionSuperFood;
    file.read(reinterpret_cast<char *>(&positionSuperFood), sizeof(positionSuperFood));
    superFood->setPosition(positionSuperFood);
    bool status;
    file.read(reinterpret_cast<char *>(&status), sizeof(status));
    dynamic_cast<SuperFood *>(superFood.get())->setEnabled(status);
    int movesLeft;
    file.read(reinterpret_cast<char *>(&movesLeft), sizeof(movesLeft));
    dynamic_cast<SuperFood *>(superFood.get())->setMovesLeft(movesLeft);
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
              << "   _____             _                    " << std::endl
              << "  / ____|           | |                                    " << std::endl
              << " | (___  _ __   __ _| | _____    __ _  __ _ _ __ ___   ___ " << std::endl
              << R"(  \___ \| '_ \ / _` | |/ / _ \  / _` |/ _` | '_ ` _ \ / _ \ )" << std::endl
              << "  ____) | | | | (_| |   <  __/ | (_| | (_| | | | | | |  __/" << std::endl
              << R"( |_____/|_| |_|\__,_|_|\_\___|  \__, |\__,_|_| |_| |_|\___|)" << std::endl
              << "                                 __/ |" << std::endl
              << "                                |___/" << std::endl
              << std::endl
              << "Info: map size " << size.first << "x" << size.second << ", borders " << Utils::Utils::boolToAlpha(borders) << std::endl;

    if (std::filesystem::exists(directoryName + "/" + gameFileName) && !std::filesystem::is_directory(directoryName + "/" + gameFileName)) {
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

void Game::settings(std::istream &input, std::ostream &output) {
    output << "Settings" << std::endl;
    output << "If you want to keep a value, insert the same value as the current one" << std::endl;
    output << "Minimum size of map is " << MIN_LENGTH << "x" << MIN_WIDTH << std::endl;
    output << "Default size of map is " << DEFAULT_LENGTH << "X" << DEFAULT_WIDTH << std::endl;
    std::pair<int, int> tmpSize{};
    do {
        output << "Length (current value is " << size.first << "): ";
        input >> tmpSize.first;
        if (!Utils::validateInput(input))
            continue;
        output << "Width (current value is " << size.second << "): ";
        input >> tmpSize.second;
        if (!Utils::validateInput(input))
            continue;
    } while (tmpSize.first < MIN_LENGTH || tmpSize.second < MIN_WIDTH);
    bool changed{};
    if (tmpSize != size) {
        changed = true;
    }
    size = tmpSize;
    output << "Change borders (On/Off) (Current value is " << Utils::Utils::boolToAlpha(borders) << ")" << std::endl;
    int status{};
    do {
        output << "Type " << !borders << " to change, " << borders << " to keep: ";
        input >> status;
        if (!Utils::validateInput(input)) {
            status = -1;
            continue;
        }
        if (status == !borders) {
            setBorders(!borders);
            output << "Borders are now set to " << Utils::boolToAlpha(borders);
            symbol = (borders) ? SYMBOL_BORDERS_ON : SYMBOL_BORDERS_OFF;
            changed = true;
        }
    } while (status != 0 && status != 1);
    if (changed)
        updateBestScores();
    writeSettings();
    updateGameFileName();
}

void Game::updateBestScores() {
    bestScores.setNameFile(size, directoryName, borders);
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
    file.read(reinterpret_cast<char *>(&borders), sizeof(borders));
    symbol = (borders) ? SYMBOL_BORDERS_ON : SYMBOL_BORDERS_OFF;
    file.close();
}

void Game::writeSettings() const {
    std::ofstream file(directoryName + "/" + settingsFileName, std::ios::binary);
    if (!file || !file.good()) {
        log("Error opening file for writing", LOGLEVEL::Warning);
        return;
    }
    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    file.write(reinterpret_cast<const char *>(&borders), sizeof(borders));
    file.close();
    if (!file.good()) {
        log("Error occurred at writing time", LOGLEVEL::Warning);
    }
}

void Game::play() {
    removeIfExists();
    Input::enableRawMode();
    while (!isGameOver()) {
        printToBufferScreen();
        std::this_thread::sleep_for(std::chrono::nanoseconds(velocity));
        system("clear");
        std::cout << bufferScreen.str();
        if (logic()) {
            save();
            Input::disableRawMode();
            break;
        }
    }
}

void Game::showKeysAndSymbols() {
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
              << snake.getSymbol() << " - Snake symbol" << std::endl
              << regularFood->getSymbol() << " - Regular food symbol" << std::endl
              << superFood->getSymbol() << " - Super food symbol" << std::endl
              << SYMBOL_BORDERS_OFF << " - Borders off" << std::endl
              << SYMBOL_BORDERS_ON << " - Borders on" << std::endl;
}

void Game::updateGameFileName() {
    gameFileName = "game_" + std::to_string(size.first) + "_" + std::to_string(size.second) + "_" + Utils::boolToAlpha(borders);
}

void Game::run() {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    std::signal(SIGINT, Utils::signalHandler);
    std::signal(SIGTSTP, Utils::signalHandler);
    readSettings();
    updateGameFileName();
    updateBestScores();
    char choice;
    do {
        system("clear");
        showMenu();
        std::cin >> choice;
        switch (choice) {
            case '0': {
                if (std::filesystem::exists(directoryName + "/" + gameFileName) && !std::filesystem::is_directory(directoryName + "/" + gameFileName)) {
                    load();
                    play();
                }
                Utils::printExitScreen();
                break;
            }
            case '1': {
                if (std::filesystem::exists(directoryName + "/" + gameFileName) && !std::filesystem::is_directory(directoryName + "/" + gameFileName)) {
                    char option;
                    std::cout << "Warning: there is a game saved and it will be deleted if a new game is started. Do you want to proceed? Type a to accept, any other key to refuse ";
                    std::cin >> option;
                    if (tolower(option) != 'a') {
                        Utils::printExitScreen();
                        break;
                    }
                }
                start();
                play();
                Utils::printExitScreen();
                break;
            }
            case '2': {
                bestScores.print(size, borders);
                Utils::printExitScreen();
                break;
            }
            case '3': {
                settings(std::cin, std::cout);
                Utils::printExitScreen();
                break;
            }
            case '4': {
                showKeysAndSymbols();
                Utils::printExitScreen();
                break;
            }
            case '5': {
                about();
                Utils::printExitScreen();
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
    system("clear");
    system("clear");
}

const Snake &Game::getSnake() const {
    return snake;
}

const Food &Game::getRegularFood() const {
    return *regularFood;
}

const Food &Game::getSuperFood() const {
    return *superFood;
}
bool Game::hasBorders() const {
    return borders;
}
void Game::setBorders(bool b) {
    Game::borders = b;
}

void Game::changeVelocity() {
    if (velocity < 20000000) return;
    int transition = 10;
    float exponentialIncrease = 1.01;
    if (foodsEaten >= transition && foodsEaten < transition * 2) {
        exponentialIncrease = 1.02;
    }
    int linearIncrease = 10000;
    if (foodsEaten < transition) {
        velocity -= linearIncrease;
    } else {
        float tempVelocity = static_cast<float>(velocity) / exponentialIncrease;
        velocity = static_cast<int>(tempVelocity);
    }
}
