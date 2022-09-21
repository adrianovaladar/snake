#include "Food.h"

Food::Food() {
    position = std::make_pair(0, 0);
}

Food::~Food() {

}

char Food::getSymbol() const {
    return symbol;
}

const std::pair<int, int> &Food::getPosition() const {
    return position;
}

void Food::setSymbol(char symbol) {
    Food::symbol = symbol;
}

void Food::setPosition(const std::pair<int, int> &position) {
    Food::position = position;
}
