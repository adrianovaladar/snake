/**
* @file Graphics.h
* @brief Defines the Graphics class for rendering the game.
*/

#ifndef SNAKE_GRAPHICS_H
#define SNAKE_GRAPHICS_H

#include <sstream>

class Game;///< Forward declaration of Game class

/**
* @class Graphics
* @brief Handles the graphical representation of the game.
*/
class Graphics {
    std::stringstream bufferScreen;///< Buffer to store the screen output.

    /**
    * @brief Prints the vertical fence and the playable area.
    * @param game Reference to the Game object.
    * @param y The current row position.
    */
    void printVerticalFenceAndPlayableArea(const Game &game, int y);

    /**
    * @brief Prints the horizontal fence of the game board.
    * @param game Reference to the Game object.
    */
    void printHorizontalFence(const Game &game);

public:
    /**
    * @brief Prints the game state to the buffer screen.
    * @param game Reference to the Game object.
    */
    void printToBufferScreen(const Game &game);

    /**
    * @brief Retrieves the buffer screen content.
    * @return A constant reference to the buffer screen.
    */
    const std::stringstream &getBufferScreen() const;

    /**
    * @brief Displays information about the game.
    */
    static void about();

    /**
    * @brief Shows key bindings and symbols used in the game.
    * @param game Reference to the Game object.
    */
    static void showKeysAndSymbols(const Game &game);

    /**
    * @brief Displays the main menu.
    * @param game Reference to the Game object.
    */
    static void showMenu(const Game &game);

    /**
    * @brief Displays the game settings.
    * @param output Output stream where the settings are displayed.
    */
    static void showSettings(std::ostream &output);
};

#endif// SNAKE_GRAPHICS_H
