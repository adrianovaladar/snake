/**
 * @file Game.h
 * @brief Declaration of the Game class and related constants for the Snake game.
 *
 * This file contains the declaration of the Game class, which manages the game logic,
 * settings, and interactions. It also defines constants for game controls and dimensions.
 */

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "BestScores.h"
#include "Food.h"
#include "Graphics.h"
#include "Player.h"
#include "Snake.h"
#include "SuperFood.h"
#include <memory>

/// The default length of the game map
constexpr int defaultLength = 80;
/// The default width of the game map
constexpr int defaultWidth = 20;

/// The minimum allowed length of the game map
constexpr int minLength = 10;
/// The minimum allowed width of the game map
constexpr int minWidth = 5;
/// The maximum allowed length of the game map
constexpr int maxLength = 1000;
/// The maximum allowed width of the game map
constexpr int maxWidth = 1000;

/// Key to move the snake upwards
constexpr char keyMoveUp = 'w';
/// Key to move the snake to the left
constexpr char keyMoveLeft = 'a';
/// Key to move the snake downwards
constexpr char keyMoveDown = 's';
/// Key to move the snake to the right
constexpr char keyMoveRight = 'd';
/// Key to pause the game
constexpr char keyPause = 'p';
/// Key to save the game state
constexpr char keySave = 'm';

/// Symbol representing an active border
constexpr char symbolBordersOn = '#';
/// Symbol representing a disabled border
constexpr char symbolBordersOff = '.';

/**
 * @class Game
 * @brief Manages the game state and controls the game flow.
 */
class Game final {
    std::pair<int, int> size; ///< Dimensions of the game map
    std::unique_ptr<Food> food; ///< Pointer to the regular food object
    std::shared_ptr<SuperFood> superFood; ///< Shared pointer to the super food object
    Snake snake; ///< The snake object representing the player
    Graphics graphics; ///< Handles game graphics rendering
    BestScores bestScores; ///< Manages the best scores in the game
    char symbol; ///< Symbol representing game elements
    int score; ///< Current game score
    std::string settingsFileName; ///< Name of the settings file
    std::string directoryName; ///< Directory where game files are stored
    std::string gameFileName; ///< Name of the game save file
    bool pause; ///< Flag indicating if the game is paused
    bool kbHit; ///< Flag for keyboard input detection
    bool borders; ///< Flag indicating if borders are enabled
    int foodsEaten; ///< Counter for eaten food
    int velocity; ///< Speed of the snake movement

    /**
     * @brief Reads a key press.
     * @return True if a key was read, false otherwise.
     */
    bool readKey();

    /**
     * @brief Updates the best scores.
     */
    void updateBestScores();

    /**
     * @brief Executes the main game loop.
     */
    void play();

    /**
     * @brief Removes the game save file if it exists.
     */
    void removeIfExists() const;

    /**
     * @brief Main game logic execution.
     * @return False if the game continues, true if it ends.
     */
    bool logic();

    /**
     * @brief Adjusts the snake's velocity.
     */
    void changeVelocity();

    /**
     * @brief Asks the player for confirmation before overwriting a save.
     * @return True if the player confirms, false otherwise.
     */
    bool confirmSaveOverwrite() const;

    /**
     * @brief Checks if the game is over.
     * @return True if the game is over, false otherwise.
     */
    bool isGameOver() const;

    /**
     * @brief Checks if the snake has eaten regular food.
     * @return True if food is eaten, false otherwise.
     */
    bool isRegularFoodEaten() const;

    /**
     * @brief Checks if the snake has eaten super food.
     * @return True if super food is eaten, false otherwise.
     */
    bool isSuperFoodEaten() const;

    /**
     * @brief Handles game settings input and output.
     * @param input Input stream for settings
     * @param output Output stream for settings
     */
    void settings(std::istream &input, std::ostream &output);

    /**
     * @brief Reads settings from a file.
     */
    void readSettings();

    /**
     * @brief Writes settings to a file.
     */
    void writeSettings() const;

    /**
     * @brief Saves the game state to a file.
     */
    void save() const;

    /**
     * @brief Loads the game state from a file.
     */
    void load();

    /**
     * @brief Updates the game file name.
     */
    void updateGameFileName();

    /**
     * @brief Checks if the game has borders enabled.
     * @return True if borders are enabled, false otherwise.
     */
    bool hasBorders() const;

    /**
     * @brief Starts the game.
     */
    void start();

public:
    /**
     * @brief Constructs a new Game object.
     */
    Game();

    /**
     * @brief Destroys the Game object.
     */
    ~Game();

    /**
     * @brief Sets the snake object.
     * @param s Snake object
     */
    void setSnake(const Snake &s);

    /**
     * @brief Gets the size of the game map.
     * @return A pair representing width and height.
     */
    [[nodiscard]] const std::pair<int, int> &getSize() const;

    /**
     * @brief Sets the regular food object.
     * @param f Unique pointer to a Food object.
     */
    void setRegularFood(std::unique_ptr<Food> f);

    /**
     * @brief Sets the super food object.
     * @param f Weak pointer to a SuperFood object.
     */
    void setSuperFood(const std::weak_ptr<SuperFood> &f);

    /**
     * @brief Runs the game loop.
     */
    void run();

    /**
     * @brief Gets the snake object.
     * @return Reference to the Snake object.
     */
    [[nodiscard]] const Snake &getSnake() const;

    /**
     * @brief Gets the regular food object.
     * @return Reference to the Food object.
     */
    [[nodiscard]] const Food &getRegularFood() const;

    /**
     * @brief Gets the super food object.
     * @return Reference to the Food object.
     */
    [[nodiscard]] const Food &getSuperFood() const;

    /**
     * @brief Sets whether the game has borders.
     * @param b Boolean value indicating if borders should be enabled.
     */
    void setBorders(bool b);

    friend class Graphics; ///< Grants Graphics class access to private members
    friend class GameTests; ///< Grants GameTests class access to private members
};

#endif // SNAKE_GAME_H
