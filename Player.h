#ifndef SNAKE_PLAYER_H
#define SNAKE_PLAYER_H

#include <string>

class Player {
    int score {};
    std::string name{};
public:
    Player();
    Player(int s, std::string n);
    virtual ~Player();
    int getScore() const;
};

#endif //SNAKE_PLAYER_H
