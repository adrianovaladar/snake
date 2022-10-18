#include "Player.h"

#include <utility>

Player::Player() = default;

Player::Player(int s, std::string n) : score(s), name(std::move(n)){

}


[[maybe_unused]] int Player::getScore() const {
    return score;
}

Player::~Player() = default;

const std::string &Player::getName() const {
    return name;
}
