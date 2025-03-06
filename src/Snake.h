/// @file snake.h
/// @brief Declaration of the Snake class.
#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <vector>

/**
* @enum Direction
* @brief Represents the movement direction of the snake.
*/
enum class Direction {
    NONE, ///< No movement
    RIGHT,///< Move right
    LEFT, ///< Move left
    UP,   ///< Move up
    DOWN  ///< Move down
};

/**
* @class Snake
* @brief Represents a snake in the game.
*/
class Snake {

private:
    std::vector<std::pair<int, int>> positions;///< Stores the positions of the snake's body.
    char symbol{};                             ///< Character symbol representing the snake.
    Direction direction;                       ///< Current movement direction of the snake.

    /**
    * @brief Moves the snake based on its current direction.
    * @param sizeMap The size of the map.
    * @param border Determines whether the snake should respect map borders.
    */
    void move(const std::pair<int, int> &sizeMap, bool border);

    /**
    * @brief Validates and sets the snake's movement direction.
    * @param d The desired direction.
    */
    void validateDirection(Direction d);

    friend class SnakeTests;///< Grants test class access to private members.
    friend class Game;      ///< Grants Game class access to private members.
    friend class GameTests; ///< Grants test class access to private members.

public:
    /**
    * @brief Constructs a new Snake object.
    */
    explicit Snake();

    /**
    * @brief Destroys the Snake object.
    */
    virtual ~Snake();

    /**
    * @brief Gets the positions of the snake.
    * @return A constant reference to the vector of positions.
    */
    [[nodiscard]] const std::vector<std::pair<int, int>> &getPositions() const;

    /**
    * @brief Gets the current direction of the snake.
    * @return The current direction of the snake.
    */
    [[nodiscard]] Direction getDirection() const;

    /**
    * @brief Sets the movement direction of the snake.
    * @param d The desired direction.
    */
    void setDirection(Direction d);

    /**
    * @brief Gets the symbol representing the snake.
    * @return The snake's symbol.
    */
    [[nodiscard]] char getSymbol() const;

    /**
    * @brief Sets the initial positions of the snake based on the map size.
    * @param sizeMap The size of the map.
    */
    void setPositions(const std::pair<int, int> &sizeMap);

    /**
    * @brief Sets the snake's positions manually.
    * @param pS A vector of position pairs.
    */
    void setPositions(const std::vector<std::pair<int, int>> &pS);

    /**
    * @brief Moves the snake forward by one step.
    * @return A reference to the updated Snake object.
    */
    Snake &operator++();
};

#endif// SNAKE_SNAKE_H
