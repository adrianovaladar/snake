#include "../src/BestScores.h"
#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>

std::string directoryName = "bestscorestests";
std::string fileName = "bestscorestests/best_scores_-1_-1_on";
std::pair testSize = {-1, -1};

TEST(BestScores, readEmptyFileBordersOn) {
    BestScores bs;
    bs.setNameFile(testSize, directoryName, true);
    bs.read();
    EXPECT_EQ(0, bs.getPlayers().size());
}

TEST(BestScores, readEmptyFileBordersOff) {
    BestScores bs;
    bs.setNameFile(testSize, directoryName, false);
    bs.read();
    EXPECT_EQ(0, bs.getPlayers().size());
}

TEST(BestScores, readFileWith1Player) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    BestScores bs;
    bs.setNameFile({-1, -1}, directoryName, true);
    std::ofstream myFile(fileName, std::ios::binary);
    size_t tempSize = 1;
    myFile.write(reinterpret_cast<const char *>(&tempSize), sizeof(tempSize));
    int tempScore = 1;
    std::string tempName = "test";
    myFile.write(reinterpret_cast<const char *>(&tempScore), sizeof(tempScore));
    std::string::size_type tempSizeName = tempName.size();
    myFile.write(reinterpret_cast<const char *>(&tempSizeName), sizeof(std::string::size_type));
    myFile.write(tempName.data(), static_cast<std::streamsize>(tempName.size()));
    myFile.close();
    bs.read();
    EXPECT_EQ(1, bs.getPlayers().size());
    remove(fileName.c_str());
    std::filesystem::remove(directoryName);
}

TEST(BestScores, readFileWithMaxPlayers) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    BestScores bs;
    bs.setNameFile(testSize, directoryName, true);
    std::ofstream myFile;
    myFile.open(fileName, std::ios::out);
    // test with all 5 positions filled
    size_t tempSize = 5;
    myFile.write(reinterpret_cast<const char *>(&tempSize), sizeof(tempSize));
    for (int i{}; i < tempSize; i++) {
        int tempScore = 1;
        std::string tempName = "test";
        myFile.write(reinterpret_cast<const char *>(&tempScore), sizeof(tempScore));
        std::string::size_type tempSizeName = tempName.size();
        myFile.write(reinterpret_cast<const char *>(&tempSizeName), sizeof(std::string::size_type));
        myFile.write(tempName.data(), static_cast<std::streamsize>(tempName.size()));
    }
    myFile.close();
    bs.read();
    EXPECT_EQ(5, bs.getPlayers().size());
    remove(fileName.c_str());
    std::filesystem::remove(directoryName);
}

TEST(BestScores, readBiggerFileThanExpected) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    BestScores bs;
    bs.setNameFile(testSize, directoryName, true);
    std::ofstream myFile;
    myFile.open(fileName, std::ios::out);
    size_t tempSize = 6;
    myFile.write(reinterpret_cast<const char *>(&tempSize), sizeof(tempSize));
    for (int i{}; i < tempSize; i++) {
        int tempScore = 1;
        std::string tempName = "test";
        myFile.write(reinterpret_cast<const char *>(&tempScore), sizeof(tempScore));
        std::string::size_type tempSizeName = tempName.size();
        myFile.write(reinterpret_cast<const char *>(&tempSizeName), sizeof(std::string::size_type));
        myFile.write(tempName.data(), static_cast<std::streamsize>(tempName.size()));
    }
    myFile.close();
    bs.read();
    EXPECT_EQ(5, bs.getPlayers().size());
    remove(fileName.c_str());
    std::filesystem::remove(directoryName);
}

TEST(BestScores, write1Player) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    BestScores bs;
    bs.setNameFile(testSize, directoryName, true);
    std::string fileNameTest = "test";
    std::ofstream myFile;
    myFile.open(fileNameTest, std::ios::out);
    myFile << "test" << std::endl;
    myFile.close();
    std::ifstream ifs;
    ifs.open(fileNameTest, std::ios::out);
    std::stringstream output;
    bs.updateAndWrite(ifs, output, 1);
    ifs.close();
    BestScores bs2;
    bs2.setNameFile(testSize, directoryName, true);
    bs2.read();
    EXPECT_EQ(1, bs2.getPlayers().size());
    remove(fileName.c_str());
    remove(fileNameTest.c_str());
    std::filesystem::remove(directoryName);
}

TEST(BestScores, write5Players) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    BestScores bs;
    bs.setNameFile(testSize, directoryName, true);
    std::string fileNameTest = "test";
    std::ofstream myFile;
    myFile.open(fileNameTest, std::ios::out);
    myFile << "test" << std::endl;
    myFile.close();
    std::ifstream ifs;
    ifs.open(fileNameTest, std::ios::out);
    std::stringstream output;
    for (int i{}; i < 5; i++) {
        bs.updateAndWrite(ifs, output, 1);
    }
    ifs.close();
    BestScores bs2;
    bs2.setNameFile(testSize, directoryName, true);
    bs2.read();
    EXPECT_EQ(5, bs2.getPlayers().size());
    remove(fileName.c_str());
    remove(fileNameTest.c_str());
    std::filesystem::remove(directoryName);
}

TEST(BestScores, writeMoreThan5Players) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    BestScores bs;
    bs.setNameFile(testSize, directoryName, true);
    std::string fileNameTest = "test";
    std::ofstream myFile;
    myFile.open(fileNameTest, std::ios::out);
    myFile.open(fileNameTest, std::ios::out);
    myFile << "test" << std::endl;
    myFile.close();
    std::ifstream ifs;
    ifs.open(fileNameTest, std::ios::out);
    std::stringstream output;
    for (int i{}; i < 10; i++) {
        bs.updateAndWrite(ifs, output, 1);
    }
    ifs.close();
    BestScores bs2;
    bs2.setNameFile(testSize, directoryName, true);
    bs2.read();
    EXPECT_EQ(5, bs2.getPlayers().size());
    remove(fileName.c_str());
    remove(fileNameTest.c_str());
    std::filesystem::remove(directoryName);
}

TEST(BestScores, write5UnsortedPlayers) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    BestScores bs;
    bs.setNameFile(testSize, directoryName, true);
    std::string fileNameTest = "test";
    std::ofstream myFile;
    myFile.open(fileNameTest, std::ios::out);
    myFile.open(fileNameTest, std::ios::out);
    myFile << "test" << std::endl;
    myFile.close();
    std::ifstream ifs;
    ifs.open(fileNameTest, std::ios::out);
    std::vector<int> scoresToCompare;
    std::stringstream output;
    for (int i{}; i < 5; i++) {
        bs.updateAndWrite(ifs, output, i);
        scoresToCompare.emplace_back(i);
    }
    ifs.close();
    std::sort(scoresToCompare.rbegin(), scoresToCompare.rend());
    BestScores bs2;
    bs2.setNameFile(testSize, directoryName, true);
    bs2.read();
    std::vector<int> scores;
    for (const auto &p: bs2.getPlayers()) {
        scores.emplace_back(p.getScore());
    }
    EXPECT_EQ(scoresToCompare, scores);
    remove(fileName.c_str());
    remove(fileNameTest.c_str());
    std::filesystem::remove(directoryName);
}

TEST(BestScores, isBestScoresWithLessThan5Players) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    BestScores bs;
    bs.setNameFile(testSize, directoryName, true);
    std::ofstream myFile;
    myFile.open(fileName, std::ios::binary);
    // test with all 2 positions filled
    size_t tempSize = 2;
    myFile.write(reinterpret_cast<const char *>(&tempSize), sizeof(tempSize));
    for (auto i{tempSize}; i > 0; i--) {
        int tempScore = static_cast<int>(i);
        std::string tempName = "test";
        myFile.write(reinterpret_cast<const char *>(&tempScore), sizeof(tempScore));
        std::string::size_type tempSizeName = tempName.size();
        myFile.write(reinterpret_cast<const char *>(&tempSizeName), sizeof(std::string::size_type));
        myFile.write(tempName.data(), static_cast<std::streamsize>(tempName.size()));
    }
    myFile.close();
    bs.read();
    EXPECT_EQ(true, bs.isBestScore(10));
    remove(fileName.c_str());
    std::filesystem::remove(directoryName);
}

TEST(BestScores, isBestScoresWith5Players) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    BestScores bs;
    bs.setNameFile(testSize, directoryName, true);
    std::ofstream myFile;
    myFile.open(fileName, std::ios::binary);
    // test with all 5 positions filled
    size_t tempSize = 5;
    myFile.write(reinterpret_cast<const char *>(&tempSize), sizeof(tempSize));
    for (auto i{tempSize}; i > 0; i--) {
        int tempScore = static_cast<int>(i);
        std::string tempName = "test";
        myFile.write(reinterpret_cast<const char *>(&tempScore), sizeof(tempScore));
        std::string::size_type tempSizeName = tempName.size();
        myFile.write(reinterpret_cast<const char *>(&tempSizeName), sizeof(std::string::size_type));
        myFile.write(tempName.data(), static_cast<std::streamsize>(tempName.size()));
    }
    myFile.close();
    bs.read();
    EXPECT_EQ(true, bs.isBestScore(10));
    remove(fileName.c_str());
    std::filesystem::remove(directoryName);
}

TEST(BestScores, isBestScoresWith5PlayersWithHigherScore) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    BestScores bs;
    bs.setNameFile(testSize, directoryName, true);
    std::ofstream myFile;
    myFile.open(fileName, std::ios::binary);
    // test with all 5 positions filled
    size_t tempSize = 5;
    myFile.write(reinterpret_cast<const char *>(&tempSize), sizeof(tempSize));
    for (auto i{tempSize}; i > 0; i--) {
        int tempScore = static_cast<int>(i);
        std::string tempName = "test";
        myFile.write(reinterpret_cast<const char *>(&tempScore), sizeof(tempScore));
        std::string::size_type tempSizeName = tempName.size();
        myFile.write(reinterpret_cast<const char *>(&tempSizeName), sizeof(std::string::size_type));
        myFile.write(tempName.data(), static_cast<std::streamsize>(tempName.size()));
    }
    myFile.close();
    bs.read();
    EXPECT_EQ(false, bs.isBestScore(0));
    remove(fileName.c_str());
    std::filesystem::remove(directoryName);
}
