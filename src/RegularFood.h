#ifndef SNAKE_REGULARFOOD_H
#define SNAKE_REGULARFOOD_H


#include "Food.h"
#include <utility>
#include <vector>

class RegularFood final : public Food {
public:
    explicit RegularFood();
    ~RegularFood() override = default;
};

#endif//SNAKE_REGULARFOOD_H
