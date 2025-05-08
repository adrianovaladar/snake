#include "Utils.h"
#include "Input.h"
#include <format>
#include <iostream>
#include <limits>
#include <logorithm/Logger.h>
#include <numeric>
#include <string>

void Utils::signalHandler(int signal) {
    system("clear");
    Input::disableRawMode();
    exit(signal);
}

void Utils::printExitScreen() {
    std::cout << std::endl
              << "Press enter to exit this screen ";
}

std::string Utils::boolToAlpha(bool status) {
    std::string text = status ? "on" : "off";
    return text;
}

bool Utils::validateInput() {
    if (std::cin.fail()) {
        // Clear input buffer and ignore invalid input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid value." << std::endl;
        return false;
    }
    return true;
}

void Utils::clearScreen() {
    if (const int code = system("clear"); code != 0) {
        logger.log(std::format("Error code: {}", code), LOGLEVEL::Error);
    }
}

bool Utils::binarySearch(const std::vector<std::pair<int, int>> &position, const std::pair<int, int> &target) {
    int begin = 0;
    auto end = static_cast<int>(position.size()) - 1;

    while (begin <= end) {
        const auto middle = std::midpoint(begin, end);// begin + (end - begin) / 2;
        if (target == position.at(middle)) {
            return true;
        }
        if (target < position.at(middle)) {
            end = middle - 1;
        } else {
            begin = middle + 1;
        }
    }
    return false;
}
