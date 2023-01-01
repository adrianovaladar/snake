#ifndef SNAKE_INPUT_H
#define SNAKE_INPUT_H

class Input {
public:
    static void enableRawMode();
    static void disableRawMode();
    static bool kbHit();
};

#endif//SNAKE_INPUT_H
