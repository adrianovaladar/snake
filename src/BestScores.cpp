#include "BestScores.h"
#include <logorithm/Logger.h>
#include <fstream>
#include <iomanip>
#include <iostream>

BestScores::~BestScores() = default;

void BestScores::setNameFile(const std::pair<int, int> &sizeGame, const std::string &directoryName, const bool &hasBorders) {
    std::stringstream nf;
    std::string b = (hasBorders) ? "on" : "off";
    nf << directoryName << "/best_scores_" << sizeGame.first << "_" << sizeGame.second << "_" << b;
    this->nameFile = nf.str();
}

void BestScores::read() {
    players.clear();
    std::ifstream myFile(nameFile, std::ios::binary);
    if (!myFile) {
        logger.log("Error opening file for reading", LOGLEVEL::Warning);
        return;
    }
    size_t playersSize;
    myFile.read(reinterpret_cast<char *>(&playersSize), sizeof(playersSize));
    if (playersSize > size) {
        logger.log("Number of players in file is " + std::to_string(playersSize) + ", only " + std::to_string(size) + "will be read", LOGLEVEL::Warning);
        playersSize = 5;
    }
    players.resize(playersSize);
    for (auto &player: players) {
        int tempScore;
        std::string tempName;
        myFile.read(reinterpret_cast<char *>(&tempScore), sizeof(tempScore));
        std::string::size_type tempSizeName;
        myFile.read(reinterpret_cast<char *>(&tempSizeName), sizeof(std::string::size_type));
        tempName.resize(tempSizeName);
        myFile.read(tempName.data(), static_cast<std::streamsize>(tempSizeName));
        player.setScore(tempScore);
        player.setName(tempName);
    }
    logger.log("Number of players read: " + std::to_string(playersSize), LOGLEVEL::Info);
    myFile.close();
}

void BestScores::updateAndWrite(std::istream &input, std::ostream &output, int score) {
    std::string n{};
    std::string name{};
    output << "Congratulations, you are one of the best scores!!" << std::endl;
    output << "Please insert your name (max 15 characters and only alphanumerical): ";
    input >> n;
    for (auto c: n) {
        if (std::isalnum(c)) {
            name += c;
        }
    }
    if (name.empty()) {
        name = "guest";
    }
    logger.log("New best score. Name: " + name + " Score: " + std::to_string(score), LOGLEVEL::Info);
    Player p{score, name.substr(0, 15)};
    std::ofstream myFile(nameFile, std::ios::binary);
    bool inserted = false;
    for (int k{}; k < players.size(); k++) {
        if (p.getScore() > players.at(k).getScore()) {
            players.insert(players.begin() + k, p);
            inserted = true;
            break;
        }
    }
    if (!inserted && players.size() < this->size) {
        players.push_back(p);
    } else if (players.size() > this->size) {
        players.pop_back();
    }
    size_t playersSize = players.size();
    myFile.write(reinterpret_cast<const char *>(&playersSize), sizeof(playersSize));
    for (const auto &player: players) {
        auto tempScore = player.getScore();
        auto tempName = player.getName();
        myFile.write(reinterpret_cast<const char *>(&tempScore), sizeof(tempScore));
        std::string::size_type tempSizeName = tempName.size();
        myFile.write(reinterpret_cast<const char *>(&tempSizeName), sizeof(std::string::size_type));
        myFile.write(tempName.data(), static_cast<std::streamsize>(tempName.size()));
    }
    myFile.close();
}

bool BestScores::isBestScore(int score) {
    if (players.size() < size) {
        return true;
    }
    if (score > players.at(players.size() - 1).getScore()) {
        return true;
    }
    return false;
}

void BestScores::print(const std::pair<int, int> &sizeGame, const bool borders) {
    std::cout << std::endl;
    std::cout << std::setw(25) << "BEST SCORES " << sizeGame.first << "X" << sizeGame.second
              << std::endl;
    std::string b = (borders) ? "ON" : "OFF";
    std::cout << std::setw(25) << "BORDERS " << b << std::endl
              << std::endl;
    if (players.empty()) {
        std::cout << "Currently there are no best scores for the current map" << std::endl;
        return;
    }
    std::cout << std::setw(8) << "POSITION" << std::setw(15 + 1) << "NAME" << std::setw(15 + 1) << "SCORE" << std::endl;
    int r{1};
    for (const auto &p: players) {
        std::cout << std::setw(8) << r << std::setw(15 + 1) << p.getName() << std::setw(15 + 1) << p.getScore() << std::endl;
        r++;
    }
}

const std::vector<Player> &BestScores::getPlayers() const {
    return players;
}
