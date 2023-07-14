#include "BestScores.h"
#include "Logger.h"
#include <fstream>
#include <iomanip>
#include <iostream>

BestScores::~BestScores() = default;

void BestScores::setNameFile(const std::pair<int, int> &sizeGame, const std::string &directoryName) {
    std::stringstream nf;
    nf << directoryName << "/best_scores_" << sizeGame.first << "_" << sizeGame.second << ".txt";
    this->nameFile = nf.str();
}

void BestScores::read() {
    players.clear();
    std::ifstream myFile;
    myFile.open(nameFile, std::ios::in);
    Player player;
    int numberPlayers{};
    while (myFile >> player) {
        players.emplace_back(player.getScore(), player.getName());
        numberPlayers++;
        if (numberPlayers == 5)
            break;
    }
    log("Number of players read: " + std::to_string(numberPlayers), LOGLEVEL::Info);
    myFile.close();
}


void BestScores::updateAndWrite(std::istream &input, std::ostream &output, int score) {
    std::ofstream myFile;
    std::string n{};
    std::string name{};
    output << "Congratulations, you are one of the best scores!!" << std::endl;
    output << "Please insert your name (max 15 characters and only alphanumerical): ";
    input >> n;
    for (auto c: n) {
        if (std::isalnum(c))
            name += c;
    }
    if (name.empty())
        name = "guest";
    log("New best score. Name: " + name + " Score: " + std::to_string(score), LOGLEVEL::Info);
    Player p{score, name.substr(0, 15)};
    myFile.open(nameFile, std::ios::out);
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
    for (const auto &r: players) {
        myFile << r.getScore() << " " << r.getName() << std::endl;
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

void BestScores::print(const std::pair<int, int> &sizeGame) {
    std::cout << std::endl;
    std::cout << std::setw(25) << "BEST SCORES " << sizeGame.first << "X" << sizeGame.second << std::endl
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
    std::cout << std::endl;
}

const std::vector<Player> &BestScores::getPlayers() const {
    return players;
}
