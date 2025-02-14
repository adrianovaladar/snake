#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <vector>

enum class Direction { NONE,
                       RIGHT,
                       LEFT,
                       UP,
                       DOWN };

class Snake {

private:
    std::vector<std::pair<int, int>> positions;
    char symbol{};
    Direction direction;
    void move(const std::pair<int, int> &sizeMap, bool border);
    void validateDirection(Direction d);
    friend class SnakeTests;
    friend class Game;
    friend class GameTests;

public:
    explicit Snake();
    virtual ~Snake();
    [[nodiscard]] const std::vector<std::pair<int, int>> &getPositions() const;
    [[nodiscard]] Direction getDirection() const;
    void setDirection(Direction d);
    [[nodiscard]] char getSymbol() const;
    void setPositions(const std::pair<int, int> &sizeMap);
    void setPositions(const std::vector<std::pair<int, int>> &pS);
    Snake &operator++();
};


#endif//SNAKE_SNAKE_H