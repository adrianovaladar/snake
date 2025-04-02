#ifndef SNAKE_BESTSCORESTESTS_H
#define SNAKE_BESTSCORESTESTS_H

#include "../src/BestScores.h"
#include <gtest/gtest.h>


class BestScoresTests : public ::testing::Test {
protected:
    std::string directoryName = "bestscorestests";
    std::string fileName = "bestscorestests/best_scores_-1_-1_on";
    std::pair<int, int> testSize = {-1, -1};
    BestScores bs;
    BestScores bs2;

    void SetUp() override {
    }

    void TearDown() override {
    }

    void read() {
        bs.read();
    }
    void read2() {
        bs2.read();
    }
    void updateAndWrite(std::istream &input, std::ostream &output, int score) {
        bs.updateAndWrite(input, output, score);
    }
    bool isBestScore(int score) {
        return bs.isBestScore(score);
    }
};


#endif//SNAKE_BESTSCORESTESTS_H
