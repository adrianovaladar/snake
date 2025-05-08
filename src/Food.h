/// @file Food.h
/// @brief Defines the Food class used in the Snake game.
#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H

#include <utility>
#include <vector>

/**
 * @class Food
 * @brief Represents a piece of food in the Snake game.
 */
class Food {
    std::pair<int, int> position = std::make_pair(-1, -1); ///< Position of the food on the map.
    char symbol = 'f'; ///< Symbol representing the food.

public:
    /**
     * @brief Constructs a Food object.
     */
    explicit Food() = default;

    /**
     * @brief Virtual destructor for Food.
     */
    virtual ~Food() = default;

    /**
     * @brief Gets the symbol representing the food.
     * @return The character symbol of the food.
     */
    [[nodiscard]] char getSymbol() const;

    /**
     * @brief Gets the position of the food.
     * @return A constant reference to the position of the food.
     */
    [[nodiscard]] const std::pair<int, int> &getPosition() const;

    /**
     * @brief Sets the position of the food.
     * @param p A pair representing the new position.
     */
    void setPosition(const std::pair<int, int> &p);

    /**
     * @brief Sets a random position for the food, avoiding the snake and other food items.
     * @param sizeMap The size of the game map.
     * @param positionsSnake The list of positions occupied by the snake.
     * @param otherFoodPosition The position of another food item to avoid overlap.
     */
    virtual void setPosition(const std::pair<int, int> &sizeMap, const std::vector<std::pair<int, int>> &positionsSnake, const std::pair<int, int> &otherFoodPosition);
protected:
    /**
     * @brief Sets the symbol representing the food.
     * @param s The character symbol to represent the food.
     */
    void setSymbol(char s);
};

#endif // SNAKE_FOOD_H
