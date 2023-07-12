#include "Food.h"

Food::Food() : symbol('f'), position(std::make_pair(-1, -1)) {}

char Food::getSymbol() const {
    return symbol;
}

const std::pair<int, int> &Food::getPosition() const {
    return position;
}

void Food::setPosition(const std::pair<int, int> &p) {
    Food::position = p;
}
