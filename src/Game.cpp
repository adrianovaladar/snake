#include "Game.h"
#include "Graphics.h"
#include "Input.h"
#include "Utils.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <logorithm/Logger.h>
#include <string>
#include <vector>

constexpr int regularFoodScore = 1;
constexpr int superFoodScore = 3;

Game::Game() : size(defaultLength, defaultWidth), score(0), directoryName("files"), pause(false), kbHit(false), borders(true), foodsEaten(0), velocity(100000000) {
    food = std::make_unique<Food>();
    superFood = std::make_shared<SuperFood>();
    settingsFileName = "settings";
    symbol = symbolBordersOn;
}

bool Game::isGameOver() const {
    if (score == std::numeric_limits<int>::max()) return true;
    // check self collision
    if (std::vector<std::pair<int, int>> snakePositions = snake.getPositions(); std::ranges::count(snakePositions, snake.getPositions().at(0)) > 1) return true;
    if (!borders) return false;
    // check border collision;
    if (auto [headSnakeX, headSnakeY] = snake.getPositions().at(0); headSnakeX < 0 || headSnakeY < 0 || headSnakeX > size.first - 1 || headSnakeY > size.second - 1) return true;
    return false;
}

void Game::start() {
    score = 0;
    foodsEaten = 0;
    velocity = 100000000;
    snake.setDirection(Direction::RIGHT);
    snake.setPositions(size);
    logger.log(std::format("Map size: {},{}", size.first, size.second), LOGLEVEL::Info);
    logger.log(std::format("Snake head position: {} {}", snake.getPositions().front().first, snake.getPositions().front().second), LOGLEVEL::Info);
    food->setPosition(size, snake.getPositions(), superFood->getPosition());
    superFood->setEnabled(false);
    pause = false;
}

bool Game::readKey(const bool mockMode, const int character) {
    int c{};
    if (Input::kbHit(mockMode, character)) {
        if (!kbHit)
            kbHit = true;
        if (mockMode) c = character;
        else c = getchar();
    }
    if (tolower(c) == keySave) {
        return true;
    }
    if (tolower(c) == keyPause) {
        pause = !pause;
    }
    if (!pause) {
        using enum Direction;
        auto d = NONE;
        if (tolower(c) == keyMoveUp)
            d = UP;
        else if (tolower(c) == keyMoveLeft)
            d = LEFT;
        else if (tolower(c) == keyMoveDown)
            d = DOWN;
        else if (tolower(c) == keyMoveRight)
            d = RIGHT;
        snake.validateDirection(d);
        snake.move(size, borders);
        if (superFood->isEnabled()) {
            superFood->decreaseMovesLeft();
        }
    }
    return false;
}

bool Game::logic() {
    if (readKey())
        return true;
    if (isRegularFoodEaten()) {
        ++snake;
        score += regularFoodScore;
        foodsEaten++;
        changeVelocity();
        food->setPosition(this->size, snake.getPositions(), superFood->getPosition());
        if (!superFood->isEnabled()) {
            superFood->setPosition(size, snake.getPositions(), food->getPosition());
            if (superFood->isEnabled()) {
                const int biggerSide = size.first > size.second ? size.first : size.second;
                superFood->setMovesLeft(static_cast<int>(static_cast<float>(biggerSide) * 0.7f));
            }
        }
    }
    if (isSuperFoodEaten()) {
        ++snake;
        score += superFoodScore;
        foodsEaten++;
        changeVelocity();
        superFood->setEnabled(false);
        superFood->Food::setPosition({-1, -1});
    }
    if (isGameOver()) {
        logger.log("Game over", LOGLEVEL::Info, {{"Snake Head x", std::to_string(snake.getPositions().front().first)}, {"Snake Head y", std::to_string(snake.getPositions().front().second)}});
        Input::disableRawMode();
        if (bestScores.isBestScore(score)) {
            kbHit = false;
            bestScores.updateAndWrite(std::cin, std::cout, score);
        }
        bestScores.print(size, borders);
    }
    return false;
}

bool Game::isRegularFoodEaten() const {
    return snake.getPositions().at(0) == food->getPosition();
}

bool Game::isSuperFoodEaten() const {
    return superFood->isEnabled() && snake.getPositions().at(0) == superFood->getPosition();
}

void Game::setSnake(const Snake &s) {
    snake = s;
}

const std::pair<int, int> &Game::getSize() const {
    return size;
}
void Game::setRegularFood(std::unique_ptr<Food> f) {
    food = std::move(f);
}

void Game::setSuperFood(const std::weak_ptr<SuperFood> &f) {
    superFood = f.lock();
}

Game::~Game() = default;

void Game::save() const {
    std::ofstream file(directoryName + "/" + gameFileName, std::ios::binary);
    if (!file || !file.good()) {
        logger.log("Error opening file for writing", LOGLEVEL::Warning);
        return;
    }
    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    file.write(reinterpret_cast<const char *>(&borders), sizeof(borders));
    const size_t positionsSize = snake.getPositions().size();
    file.write(reinterpret_cast<const char *>(&positionsSize), sizeof(positionsSize));
    file.write(reinterpret_cast<const char *>(snake.getPositions().data()), static_cast<std::streamsize>(positionsSize * sizeof(std::pair<int, int>)));
    const Direction d = snake.getDirection();
    file.write(reinterpret_cast<const char *>(&d), sizeof(d));
    file.write(reinterpret_cast<const char *>(&food->getPosition()), sizeof(food->getPosition()));
    file.write(reinterpret_cast<const char *>(&superFood->getPosition()), sizeof(superFood->getPosition()));
    const bool enabled = superFood->isEnabled();
    file.write(reinterpret_cast<const char *>(&enabled), sizeof(enabled));
    const int movesLeft = superFood->getMovesLeft();
    file.write(reinterpret_cast<const char *>(&movesLeft), sizeof(movesLeft));
    file.write(reinterpret_cast<const char *>(&score), sizeof(score));

    file.close();
    if (!file.good()) {
        logger.log("Error occurred at writing time", LOGLEVEL::Warning);
    }
}

void Game::load() {
    std::ifstream file(directoryName + "/" + gameFileName, std::ios::binary);
    if (!file) {
        logger.log("Error opening file for reading", LOGLEVEL::Warning);
        return;
    }
    std::pair<int, int> sizeMap;
    file.read(reinterpret_cast<char *>(&sizeMap), sizeof(sizeMap));
    if (sizeMap != size) {
        logger.log("Different map size found in the file", LOGLEVEL::Warning);
        return;
    }
    bool b;
    file.read(reinterpret_cast<char *>(&b), sizeof(b));
    if (b != borders) {
        logger.log("Different border status found in the file", LOGLEVEL::Warning);
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
    food->setPosition(positionRegularFood);
    std::pair<int, int> positionSuperFood;
    file.read(reinterpret_cast<char *>(&positionSuperFood), sizeof(positionSuperFood));
    superFood->Food::setPosition(positionSuperFood);
    bool status;
    file.read(reinterpret_cast<char *>(&status), sizeof(status));
    superFood->setEnabled(status);
    int movesLeft;
    file.read(reinterpret_cast<char *>(&movesLeft), sizeof(movesLeft));
    superFood->setMovesLeft(movesLeft);
    file.read(reinterpret_cast<char *>(&score), sizeof(score));
    file.close();
    pause = true;
}

void Game::removeIfExists() const {
    if (std::filesystem::exists(directoryName + "/" + gameFileName)) {
        std::filesystem::remove(directoryName + "/" + gameFileName);
    }
}

void Game::settings(std::istream &input, std::ostream &output) {
    Graphics::showSettings(output);
    std::pair<int, int> tmpSize{};
    do {
        output << "Length (current value is " << size.first << "): ";
        input >> tmpSize.first;
        if (!Utils::validateInput())
            continue;
        output << "Width (current value is " << size.second << "): ";
        input >> tmpSize.second;
    } while (tmpSize.first < minLength || tmpSize.second < minWidth || tmpSize.first > maxLength || tmpSize.second > maxWidth);
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
        if (!Utils::validateInput()) {
            status = -1;
            continue;
        }
        if (status == !borders) {
            setBorders(!borders);
            output << "Borders are now set to " << Utils::boolToAlpha(borders);
            symbol = borders ? symbolBordersOn : symbolBordersOff;
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

void Game::readSettings() {
    std::ifstream file(directoryName + "/" + settingsFileName, std::ios::binary);
    if (!file) {
        logger.log("Error opening file for reading", LOGLEVEL::Warning);
        return;
    }
    file.read(reinterpret_cast<char *>(&size), sizeof(size));
    file.read(reinterpret_cast<char *>(&borders), sizeof(borders));
    symbol = borders ? symbolBordersOn : symbolBordersOff;
    file.close();
}

void Game::writeSettings() const {
    std::ofstream file(directoryName + "/" + settingsFileName, std::ios::binary);
    if (!file || !file.good()) {
        logger.log("Error opening file for writing", LOGLEVEL::Warning);
        return;
    }
    file.write(reinterpret_cast<const char *>(&size), sizeof(size));
    file.write(reinterpret_cast<const char *>(&borders), sizeof(borders));
    file.close();
    if (!file.good()) {
        logger.log("Error occurred at writing time", LOGLEVEL::Warning);
    }
}

void Game::play() {
    removeIfExists();
    Input::enableRawMode();
    while (!isGameOver()) {
        graphics.printToBufferScreen(*this);
        std::this_thread::sleep_for(std::chrono::nanoseconds(velocity));
        Utils::clearScreen();
        std::cout << graphics.getBufferScreen().str();
        if (logic()) {
            save();
            Input::disableRawMode();
            break;
        }
    }
}

void Game::updateGameFileName() {
    gameFileName = std::format("game_{}_{}_{}", size.first, size.second, borders);
}

bool Game::confirmSaveOverwrite() const {
    if (std::filesystem::exists(directoryName + "/" + gameFileName) && !std::filesystem::is_directory(directoryName + "/" + gameFileName)) {
        char option;
        std::cout << "Warning: there is a game saved and it will be deleted if a new game is started. "
                     "Do you want to proceed? Type 'a' to accept, any other key to refuse ";
        std::cin >> option;
        return tolower(option) == 'a';
    }
    return true;
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
        Utils::clearScreen();
        kbHit = false;
        Graphics::showMenu(*this);
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
                if (!confirmSaveOverwrite()) {
                    Utils::printExitScreen();
                    break;
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
                Graphics::showKeysAndSymbols(*this);
                Utils::printExitScreen();
                break;
            }
            case '5': {
                Graphics::about();
                Utils::printExitScreen();
                break;
            }
            default: {
                break;
            }
        }
        if (choice == '0' || choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5') {
            if (!kbHit) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin.get();
        }
    } while (choice != '9');
    Utils::clearScreen();
}

const Snake &Game::getSnake() const {
    return snake;
}

const Food &Game::getRegularFood() const {
    return *food;
}

const Food &Game::getSuperFood() const {
    return *superFood;
}
bool Game::hasBorders() const {
    return borders;
}
void Game::setBorders(const bool b) {
    borders = b;
}

void Game::changeVelocity() {
    if (velocity < 20000000) return;
    constexpr int transition = 10;
    float exponentialIncrease = 1.01f;
    if (foodsEaten >= transition && foodsEaten < transition * 2) {
        exponentialIncrease = 1.02f;
    }
    if (foodsEaten < transition) {
        constexpr int linearIncrease = 10000;
        velocity -= linearIncrease;
    } else {
        const float tempVelocity = static_cast<float>(velocity) / exponentialIncrease;
        velocity = static_cast<int>(tempVelocity);
    }
}
