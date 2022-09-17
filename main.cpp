#include <iostream>

void printLine(const int &x, const char & symbol) {
    for (int i {}; i < x ; i++) {
        std::cout << symbol;
    }
    std::cout << std::endl;
}

void printColumns(const int &x, const int &y, const char &symbol) {
    for(int j {}; j < y ; j++) {
        if (j == 0 || j == y - 1)
            std::cout << symbol;
        else
            std:: cout << " ";
    }
    std::cout << std::endl;
}

void drawMap(const int &x, const int &y, const char &symbol) {
    std::cout << "Snake game" << std::endl;
    printLine(x, symbol);
    for(int j {}; j < y ; j++)
        printColumns(x, y, symbol);
    printLine(x, symbol);
}


int main () {
    drawMap(30, 30, '#');
    return 0;
}