/**
* @file Input.h
* @brief Declares the Input class for handling keyboard input in the Snake game.
*
* The Input class provides static methods for enabling and disabling raw keyboard mode
* and detecting key presses.
*/

#ifndef SNAKE_INPUT_H
#define SNAKE_INPUT_H

/**
* @class Input
* @brief Handles keyboard input for the Snake game.
*
* The Input class provides methods to enable raw mode (which allows capturing key presses
* without requiring Enter), disable raw mode, and check if a key has been pressed.
*/
class Input {
public:
    /**
    * @brief Enables raw keyboard input mode.
    *
    * This method configures the terminal to allow key presses to be detected
    * without requiring the user to press Enter.
    */
    static void enableRawMode(bool mockMode = false);

    /**
    * @brief Disables raw keyboard input mode.
    *
    * Restores the terminal settings to their original state.
    */
    static void disableRawMode(bool mockMode = false);

    /**
    * @brief Checks if a key has been pressed.
    * @return True if a key has been pressed, otherwise false.
    */
    static bool kbHit(bool mockMode = false, int character = 0);
};

#endif// SNAKE_INPUT_H
