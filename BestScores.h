#ifndef SNAKE_BESTSCORES_H
#define SNAKE_BESTSCORES_H

#include <vector>
#include "Player.h"


class BestScores {
    std::vector<Player> players;
    std::string nameFile;
    const int size;
public:
    explicit BestScores() : size(5) {};
    virtual ~BestScores();
    void setNameFile(const std::pair<int, int> &sizeGame);
    void read();
    void updateAndWrite(int score);
    bool isBestScore(int score);
    void print();

};
#endif //SNAKE_BESTSCORES_H
