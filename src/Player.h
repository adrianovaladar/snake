/**
* @file Player.h
* @brief Defines the Player class for the Snake game.
*
* This file declares the Player class, which manages the player's score and name.
*/

#ifndef SNAKE_PLAYER_H
#define SNAKE_PLAYER_H

#include <iostream>
#include <string>

/**
* @class Player
* @brief Represents a player in the Snake game.
*
* The Player class stores a player's name and score, and provides methods
* to access and modify these attributes.
*/
class Player {
    int score{};     ///< The player's score.
    std::string name;///< The player's name.

public:
    /**
    * @brief Default constructor for Player.
    *
    * Initializes a Player object with default values.
    */
    Player();

    /**
    * @brief Parameterized constructor for Player.
    * @param s Initial score of the player.
    * @param n Name of the player.
    */
    Player(int s, std::string n);

    /**
    * @brief Destructor for Player.
    */
    virtual ~Player();

    /**
    * @brief Gets the player's score.
    * @return The score of the player.
    */
    [[maybe_unused]] [[nodiscard]] int getScore() const;

    /**
    * @brief Gets the player's name.
    * @return A constant reference to the player's name.
    */
    [[nodiscard]] const std::string &getName() const;

    /**
    * @brief Overloads the input stream operator for Player.
    *
    * Allows input of a Player object using an input stream.
    * @param is Input stream.
    * @param p Player object to be modified.
    * @return Reference to the input stream.
    */
    friend std::istream &operator>>(std::istream &is, Player &p) {
        is >> p.score >> p.name;
        return is;
    }

    /**
    * @brief Sets the player's score.
    * @param s The new score to be assigned.
    */
    void setScore(int s);

    /**
    * @brief Sets the player's name.
    * @param n The new name to be assigned.
    */
    void setName(std::string_view n);
};

#endif// SNAKE_PLAYER_H
