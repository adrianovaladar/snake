#include "../src/BestScores.h"
#include "gtest/gtest.h"
#include <fstream>

TEST(BestScores, read) {
    BestScores bs;
    bs.setNameFile({-1, -1});
    std::ofstream myFile;
    myFile.open("best_scores_-1_-1.txt", std::ios::out);
    myFile << 1 << " test";
    myFile.close();
    bs.read();
    EXPECT_EQ(1, bs.getPlayers().size());
}
