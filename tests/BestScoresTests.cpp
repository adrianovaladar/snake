#include "../src/BestScores.h"
#include "gtest/gtest.h"
#include <fstream>

std::string fileName = "best_scores_-1_-1.txt";
std::pair testSize = {-1, -1};

TEST(BestScores, readEmptyFile) {
    BestScores bs;
    bs.setNameFile(testSize);
    bs.read();
    EXPECT_EQ(0, bs.getPlayers().size());
}

TEST(BestScores, readFileWith1Player) {
    BestScores bs;
    bs.setNameFile({-1, -1});
    std::ofstream myFile;
    myFile.open(fileName, std::ios::out);
    myFile << 1 << " test" << std::endl;
    bs.read();
    EXPECT_EQ(1, bs.getPlayers().size());
    myFile.close();
    remove(fileName.c_str());
}

TEST(BestScores, readFileWithMaxPlayers) {
    BestScores bs;
    bs.setNameFile(testSize);
    std::ofstream myFile;
    myFile.open(fileName, std::ios::out);
    // test with all 5 positions filled
    for (int i{}; i < 5; i++) {
        myFile << 1 << " test" << std::endl;
    }
    bs.read();
    EXPECT_EQ(5, bs.getPlayers().size());
    myFile.close();
    remove(fileName.c_str());
}

TEST(BestScores, readBiggerFileThanExpected) {
    BestScores bs;
    bs.setNameFile(testSize);
    std::ofstream myFile;
    myFile.open(fileName, std::ios::out);
    for (int i{}; i < 6; i++) {
        myFile << 1 << " test" << std::endl;
    }
    bs.read();
    EXPECT_EQ(5, bs.getPlayers().size());
    myFile.close();
    remove(fileName.c_str());
}

TEST(BestScores, write1Player) {
    BestScores bs;
    bs.setNameFile(testSize);
    std::string fileNameTest = "test";
    std::ofstream myFile;
    myFile.open(fileNameTest, std::ios::out);
    myFile << "test" << std::endl;
    myFile.close();
    std::ifstream ifs;
    ifs.open(fileNameTest, std::ios::out);
    bs.updateAndWrite(ifs, 1);
    ifs.close();
    BestScores bs2;
    bs2.setNameFile(testSize);
    bs2.read();
    EXPECT_EQ(1, bs2.getPlayers().size());
    remove(fileName.c_str());
    remove(fileNameTest.c_str());
}

TEST(BestScores, write5Players) {
    BestScores bs;
    bs.setNameFile(testSize);
    std::string fileNameTest = "test";
    std::ofstream myFile;
    myFile.open(fileNameTest, std::ios::out);
    myFile << "test" << std::endl;
    myFile.close();
    std::ifstream ifs;
    ifs.open(fileNameTest, std::ios::out);
    for (int i{}; i < 5; i++) {
        bs.updateAndWrite(ifs, 1);
    }
    ifs.close();
    BestScores bs2;
    bs2.setNameFile(testSize);
    bs2.read();
    EXPECT_EQ(1, bs2.getPlayers().size());
    remove(fileName.c_str());
    remove(fileNameTest.c_str());
}

TEST(BestScores, writeMoreThan5Players) {
    BestScores bs;
    bs.setNameFile(testSize);
    std::string fileNameTest = "test";
    std::ofstream myFile;
    myFile.open(fileNameTest, std::ios::out);
    myFile.open(fileNameTest, std::ios::out);
    myFile << "test" << std::endl;
    myFile.close();
    std::ifstream ifs;
    ifs.open(fileNameTest, std::ios::out);
    for (int i{}; i < 10; i++) {
        bs.updateAndWrite(ifs, 1);
    }
    ifs.close();
    BestScores bs2;
    bs2.setNameFile(testSize);
    bs2.read();
    EXPECT_EQ(5, bs2.getPlayers().size());
    remove(fileName.c_str());
    remove(fileNameTest.c_str());
}

TEST(BestScores, write5UnsortedPlayers) {
    BestScores bs;
    bs.setNameFile(testSize);
    std::string fileNameTest = "test";
    std::ofstream myFile;
    myFile.open(fileNameTest, std::ios::out);
    myFile.open(fileNameTest, std::ios::out);
    myFile << "test" << std::endl;
    myFile.close();
    std::ifstream ifs;
    ifs.open(fileNameTest, std::ios::out);
    std::vector<int> scoresToCompare;
    for (int i{}; i < 5; i++) {
        bs.updateAndWrite(ifs, i);
        scoresToCompare.emplace_back(i);
    }
    ifs.close();
    std::sort(scoresToCompare.rbegin(), scoresToCompare.rend());
    BestScores bs2;
    bs2.setNameFile(testSize);
    bs2.read();
    std::vector<int> scores;
    for (auto p: bs2.getPlayers()) {
        scores.emplace_back(p.getScore());
    }
    EXPECT_EQ(scoresToCompare, scores);
    remove(fileName.c_str());
    remove(fileNameTest.c_str());
}

TEST(BestScores, isBestScoresWithLessThan5Players) {
    BestScores bs;
    bs.setNameFile(testSize);
    std::ofstream myFile;
    myFile.open(fileName, std::ios::out);
    // test with all 2 positions filled
    for (int i{2}; i > 0; i--) {
        myFile << i << " test" << std::endl;
    }
    myFile.close();
    bs.read();
    EXPECT_EQ(true, bs.isBestScore(10));
    remove(fileName.c_str());
}

TEST(BestScores, isBestScoresWith5Players) {
    BestScores bs;
    bs.setNameFile(testSize);
    std::ofstream myFile;
    myFile.open(fileName, std::ios::out);
    // test with all 5 positions filled
    for (int i{5}; i > 0; i--) {
        myFile << i << " test" << std::endl;
    }
    myFile.close();
    bs.read();
    EXPECT_EQ(true, bs.isBestScore(10));
    remove(fileName.c_str());
}

TEST(BestScores, isBestScoresWith5PlayersWithHigherScore) {
    BestScores bs;
    bs.setNameFile(testSize);
    std::ofstream myFile;
    myFile.open(fileName, std::ios::out);
    // test with all 5 positions filled
    for (int i{5}; i > 0; i--) {
        myFile << i << " test" << std::endl;
    }
    myFile.close();
    bs.read();
    EXPECT_EQ(false, bs.isBestScore(0));
    remove(fileName.c_str());
}
