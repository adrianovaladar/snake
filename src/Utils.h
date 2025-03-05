#ifndef SNAKE_UTILS_H
#define SNAKE_UTILS_H

#include <string>
#include <vector>

class Utils {
public:
    static void signalHandler(int signal);
    static void printExitScreen();
    static std::string boolToAlpha(bool status);
    static bool validateInput();
    static void clearScreen();
    static bool binarySearch(const std::vector<std::pair<int, int>> &position, const std::pair<int, int> &target);
};


#endif//SNAKE_UTILS_H
