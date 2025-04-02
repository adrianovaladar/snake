#ifndef SNAKE_BESTSCORES_H
#define SNAKE_BESTSCORES_H

#include "Player.h"
#include <vector>

constexpr int sizeBestScores = 5;

/**
 * @class BestScores
 * @brief Manages the best scores for the Snake game.
 *
 * This class reads, updates and stores the best scores achieved in the game.
 */
class BestScores {
    std::vector<Player> players;    ///< List of top players and their scores.
    std::string nameFile;           ///< File name where best scores are stored.
    const int size = sizeBestScores;///< Maximum number of best scores stored.

    /**
     * @brief Reads the best scores from the file.
     */
    void read();

    /**
     * @brief Updates the best scores and writes them to the file.
     * @param input Input stream to read from.
     * @param output Output stream to write to.
     * @param score The new score to be considered.
     */
    void updateAndWrite(std::istream &input, std::ostream &output, int score);

    /**
     * @brief Checks if a given score qualifies as a best score.
     * @param score The score to check.
     * @return True if the score is among the best scores, false otherwise.
     */
    bool isBestScore(int score);

    /**
     * @brief Prints the best scores to the console.
     * @param sizeGame The size of the game grid.
     * @param borders Indicates whether the game has borders.
     */
    void print(const std::pair<int, int> &sizeGame, bool borders) const;

public:
    /**
     * @brief Constructs a BestScores object and initializes it.
     */
    explicit BestScores();

    /**
     * @brief Destroys the BestScores object.
     */
    virtual ~BestScores();

    /**
     * @brief Sets the file name for storing best scores.
     * @param sizeGame The size of the game grid.
     * @param directoryName The directory where the file is stored.
     * @param borders Indicates whether the game has borders.
     */
    void setNameFile(const std::pair<int, int> &sizeGame, const std::string &directoryName, const bool &borders);

    /**
     * @brief Gets the list of top players and their scores.
     * @return A constant reference to the vector of players.
     */
    [[nodiscard]] const std::vector<Player> &getPlayers() const;

    friend class BestScoresTests;///< Allows BestScoresTests to access private members for testing.
    friend class Game;           ///< Allows Game class to access private members.
};

#endif// SNAKE_BESTSCORES_H
