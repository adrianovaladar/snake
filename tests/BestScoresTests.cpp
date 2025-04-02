#include "BestScoresTests.h"
#include "../src/BestScores.h"
#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>

TEST_F(BestScoresTests, readEmptyFileBordersOn) {
    bs.setNameFile(testSize, directoryName, true);
    read();
    EXPECT_EQ(0, bs.getPlayers().size());
}

TEST_F(BestScoresTests, readEmptyFileBordersOff) {
    bs.setNameFile(testSize, directoryName, false);
    read();
    EXPECT_EQ(0, bs.getPlayers().size());
}

TEST_F(BestScoresTests, readFileWith1Player) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
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
    read();
    EXPECT_EQ(1, bs.getPlayers().size());
    remove(fileName.c_str());
    std::filesystem::remove(directoryName);
}

TEST_F(BestScoresTests, readFileWithMaxPlayers) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
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
    read();
    EXPECT_EQ(5, bs.getPlayers().size());
    remove(fileName.c_str());
    std::filesystem::remove(directoryName);
}

TEST_F(BestScoresTests, readBiggerFileThanExpected) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
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
    read();
    EXPECT_EQ(5, bs.getPlayers().size());
    remove(fileName.c_str());
    std::filesystem::remove(directoryName);
}

TEST_F(BestScoresTests, write1Player) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    bs.setNameFile(testSize, directoryName, true);
    std::string fileNameTest = "test";
    std::ofstream myFile;
    myFile.open(fileNameTest, std::ios::out);
    myFile << "test" << std::endl;
    myFile.close();
    std::ifstream ifs;
    ifs.open(fileNameTest, std::ios::out);
    std::stringstream output;
    updateAndWrite(ifs, output, 1);
    ifs.close();
    bs2.setNameFile(testSize, directoryName, true);
    read2();
    EXPECT_EQ(1, bs2.getPlayers().size());
    remove(fileName.c_str());
    remove(fileNameTest.c_str());
    std::filesystem::remove(directoryName);
}

TEST_F(BestScoresTests, write5Players) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
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
        updateAndWrite(ifs, output, 1);
    }
    ifs.close();
    bs2.setNameFile(testSize, directoryName, true);
    read2();
    EXPECT_EQ(5, bs2.getPlayers().size());
    remove(fileName.c_str());
    remove(fileNameTest.c_str());
    std::filesystem::remove(directoryName);
}

TEST_F(BestScoresTests, writeMoreThan5Players) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
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
        updateAndWrite(ifs, output, 1);
    }
    ifs.close();
    bs2.setNameFile(testSize, directoryName, true);
    read2();
    EXPECT_EQ(5, bs2.getPlayers().size());
    remove(fileName.c_str());
    remove(fileNameTest.c_str());
    std::filesystem::remove(directoryName);
}

TEST_F(BestScoresTests, write5UnsortedPlayers) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
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
        updateAndWrite(ifs, output, i);
        scoresToCompare.emplace_back(i);
    }
    ifs.close();
    std::sort(scoresToCompare.rbegin(), scoresToCompare.rend());
    bs2.setNameFile(testSize, directoryName, true);
    read2();
    std::vector<int> scores;
    for (const auto &p: bs2.getPlayers()) {
        scores.emplace_back(p.getScore());
    }
    EXPECT_EQ(scoresToCompare, scores);
    remove(fileName.c_str());
    remove(fileNameTest.c_str());
    std::filesystem::remove(directoryName);
}

TEST_F(BestScoresTests, isBestScoresWithLessThan5Players) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    bs.setNameFile(testSize, directoryName, true);
    std::ofstream myFile;
    myFile.open(fileName, std::ios::binary);
    // test with all 2 positions filled
    size_t tempSize = 2;
    myFile.write(reinterpret_cast<const char *>(&tempSize), sizeof(tempSize));
    for (auto i{tempSize}; i > 0; i--) {
        auto tempScore = static_cast<int>(i);
        std::string tempName = "test";
        myFile.write(reinterpret_cast<const char *>(&tempScore), sizeof(tempScore));
        std::string::size_type tempSizeName = tempName.size();
        myFile.write(reinterpret_cast<const char *>(&tempSizeName), sizeof(std::string::size_type));
        myFile.write(tempName.data(), static_cast<std::streamsize>(tempName.size()));
    }
    myFile.close();
    read();
    EXPECT_EQ(true, isBestScore(10));
    remove(fileName.c_str());
    std::filesystem::remove(directoryName);
}

TEST_F(BestScoresTests, isBestScoresWith5Players) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    bs.setNameFile(testSize, directoryName, true);
    std::ofstream myFile;
    myFile.open(fileName, std::ios::binary);
    // test with all 5 positions filled
    size_t tempSize = 5;
    myFile.write(reinterpret_cast<const char *>(&tempSize), sizeof(tempSize));
    for (auto i{tempSize}; i > 0; i--) {
        auto tempScore = static_cast<int>(i);
        std::string tempName = "test";
        myFile.write(reinterpret_cast<const char *>(&tempScore), sizeof(tempScore));
        std::string::size_type tempSizeName = tempName.size();
        myFile.write(reinterpret_cast<const char *>(&tempSizeName), sizeof(std::string::size_type));
        myFile.write(tempName.data(), static_cast<std::streamsize>(tempName.size()));
    }
    myFile.close();
    read();
    EXPECT_EQ(true, isBestScore(10));
    remove(fileName.c_str());
    std::filesystem::remove(directoryName);
}

TEST_F(BestScoresTests, isBestScoresWith5PlayersWithHigherScore) {
    if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
        std::filesystem::create_directory(directoryName);
    }
    bs.setNameFile(testSize, directoryName, true);
    std::ofstream myFile;
    myFile.open(fileName, std::ios::binary);
    // test with all 5 positions filled
    size_t tempSize = 5;
    myFile.write(reinterpret_cast<const char *>(&tempSize), sizeof(tempSize));
    for (auto i{tempSize}; i > 0; i--) {
        auto tempScore = static_cast<int>(i);
        std::string tempName = "test";
        myFile.write(reinterpret_cast<const char *>(&tempScore), sizeof(tempScore));
        std::string::size_type tempSizeName = tempName.size();
        myFile.write(reinterpret_cast<const char *>(&tempSizeName), sizeof(std::string::size_type));
        myFile.write(tempName.data(), static_cast<std::streamsize>(tempName.size()));
    }
    myFile.close();
    read();
    EXPECT_EQ(false, isBestScore(0));
    remove(fileName.c_str());
    std::filesystem::remove(directoryName);
}
