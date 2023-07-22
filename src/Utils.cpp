#include "Utils.h"
#include "Input.h"
#include <iostream>
#include <limits>
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
