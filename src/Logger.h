#ifndef SNAKE_LOGGER_H
#define SNAKE_LOGGER_H

#include <chrono>
#include <iostream>
#include <source_location>

enum class LOGLEVEL : char {
    Info = 'I',
    Warning = 'W',
    Error = 'E'
};

class Logger {
private:
    static Logger *instancePtr;
    Logger() = default;

public:
    // deleting copy constructor
    Logger(const Logger &obj) = delete;

    static Logger *getInstance() {
        if (instancePtr == nullptr) {
            instancePtr = new Logger();
            return instancePtr;
        } else {
            return instancePtr;
        }
    }
    void log(const std::string &text, LOGLEVEL level, std::source_location source = std::source_location::current());
};

#endif//SNAKE_LOGGER_H
