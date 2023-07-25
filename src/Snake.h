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

public:
    explicit Snake();
    virtual ~Snake();
    [[nodiscard]] const std::vector<std::pair<int, int>> &getPositions() const;
    [[nodiscard]] Direction getDirection() const;
    void setDirection(Direction d);
    [[nodiscard]] char getSymbol() const;
    void move(const std::pair<int, int> &sizeMap, bool border);
    void validateDirection(Direction d);
    void setPositions(const std::vector<std::pair<int, int>> &pS);
    void setPositions(const std::pair<int, int> &sizeMap);
    Snake &operator++();
};


#endif//SNAKE_SNAKE_H