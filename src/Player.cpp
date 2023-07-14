#include "Player.h"
#include <iostream>
#include <utility>

Player::Player() = default;

Player::Player(int s, std::string n) : score(s), name(std::move(n)) {
}

[[maybe_unused]] int Player::getScore() const {
    return score;
}

Player::~Player() = default;

const std::string &Player::getName() const {
    return name;
}

std::istream &operator>>(std::istream &is, Player &p) {
    is >> p.score >> p.name;
    return is;
}
