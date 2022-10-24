#ifndef SNAKE_PLAYER_H
#define SNAKE_PLAYER_H

#include <string>

class Player {
    int score{};
    std::string name{};

public:
    Player();
    Player(int s, std::string n);
    virtual ~Player();
    [[maybe_unused]] [[nodiscard]] int getScore() const;
    [[nodiscard]] const std::string &getName() const;
};

#endif//SNAKE_PLAYER_H
