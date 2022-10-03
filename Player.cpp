#include "Player.h"

Player::Player() {

}

Player::Player(int s, std::string n) : score(s), name(n){

}


int Player::getScore() const {
    return score;
}

Player::~Player() {

}
