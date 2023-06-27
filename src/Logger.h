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
public:
    static void log(const std::string &text, LOGLEVEL level, std::source_location source);
};

void log(const std::string &text, LOGLEVEL level, std::source_location source = std::source_location::current());

#endif//SNAKE_LOGGER_H
