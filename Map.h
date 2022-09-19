#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H


class Map {
private:
    int x;
    int y;
    char symbol;
public:
    Map(int x, int y, char symbol) : x(x), y(y), symbol(symbol) {}
    void drawMap();
    void printVerticalFence();
    void printHorizontalFence();
};



#endif //SNAKE_MAP_H
