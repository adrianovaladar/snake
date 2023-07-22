//
// Created by adrianovaladar on 22-07-2023.
//

#ifndef SNAKE_UTILS_H
#define SNAKE_UTILS_H

#include <string>

class Utils {
public:
    static void signalHandler(int signal);
    static void printExitScreen();
    static std::string boolToAlpha(bool status);
    static bool validateInput(std::istream &input);
};


#endif//SNAKE_UTILS_H
