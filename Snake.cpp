//
// Created by Admin on 19/09/2022.
//

#include "Snake.h"
#include <vector>

Snake::Snake() {
    std::vector<int> x {2, 3, 4};
    std::vector<int> y {4, 4, 4};
    positionsSnake.push_back(x);
    positionsSnake.push_back(y);
}
