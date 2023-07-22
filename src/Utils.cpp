#include "Utils.h"
#include "Input.h"
#include <iostream>
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