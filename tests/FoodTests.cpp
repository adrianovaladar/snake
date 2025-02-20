#include "FoodTests.h"
#include "../src/Food.h"
#include "../src/SuperFood.h"
#include "gtest/gtest.h"
#include <algorithm>

TEST_F(FoodTests, setPositionFood) {
    testSetPosition(food);
}

TEST_F(FoodTests, setPositionSuperFood) {
    testSetPosition(superFood);
}
