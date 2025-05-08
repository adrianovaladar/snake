/// @file SuperFood.h
/// @brief Defines the SuperFood class used in the Snake game.
#ifndef SNAKE_SUPERFOOD_H
#define SNAKE_SUPERFOOD_H

#include "Food.h"
#include <utility>
#include <vector>

/**
 * @class SuperFood
 * @brief Represents a special type of food with limited-time effects in the Snake game.
 */
class SuperFood final : public Food {
    bool enabled; ///< Indicates whether the SuperFood is active.
    int movesLeft; ///< Number of moves left before the SuperFood disappears.

public:
    /**
     * @brief Brings the base class overload of setPosition into scope.
     *
     * This allows the SuperFood class to use the base class's setPosition(const std::pair<int, int>&)
     * in addition to its own overridden version with three parameters.
     */
    using Food::setPosition;
    /**
     * @brief Constructs a SuperFood object.
     */
    explicit SuperFood();

    /**
     * @brief Destructor for SuperFood.
     */
    ~SuperFood() override = default;

    /**
     * @brief Sets a random position for the SuperFood, avoiding the snake and other food items.
     * @param sizeMap The size of the game map.
     * @param positionsSnake The list of positions occupied by the snake.
     * @param otherFoodPosition The position of another food item to avoid overlap.
     */
    void setPosition(const std::pair<int, int> &sizeMap, const std::vector<std::pair<int, int>> &positionsSnake, const std::pair<int, int> &otherFoodPosition) override;

    /**
     * @brief Sets the number of moves left before the SuperFood disappears.
     * @param moves The number of moves.
     */
    void setMovesLeft(int moves);

    /**
     * @brief Decreases the remaining moves left for the SuperFood.
     */
    void decreaseMovesLeft();

    /**
     * @brief Checks if the SuperFood is enabled.
     * @return True if enabled, false otherwise.
     */
    [[nodiscard]] bool isEnabled() const;

    /**
     * @brief Sets the enabled status of the SuperFood.
     * @param status The new status.
     */
    void setEnabled(bool status);

    /**
     * @brief Gets the remaining moves left before the SuperFood disappears.
     * @return The number of remaining moves.
     */
    [[nodiscard]] int getMovesLeft() const;
};


#endif//SNAKE_SUPERFOOD_H
