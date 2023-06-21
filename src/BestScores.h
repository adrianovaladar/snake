#ifndef SNAKE_BESTSCORES_H
#define SNAKE_BESTSCORES_H

#include "Player.h"
#include <vector>


class BestScores {
    std::vector<Player> players;
    std::string nameFile;
    const int size;

public:
    explicit BestScores() : size(5){};
    virtual ~BestScores();
    void setNameFile(const std::pair<int, int> &sizeGame);
    void read();
    void updateAndWrite(std::istream &input, int score);
    bool isBestScore(int score);
    void print();
    [[nodiscard]] const std::vector<Player> &getPlayers() const;
};
#endif//SNAKE_BESTSCORES_H
