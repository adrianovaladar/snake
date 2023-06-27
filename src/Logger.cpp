#include "Logger.h"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <source_location>
#include <sstream>

std::string sourceToString(std::source_location const source) {
    std::stringstream ss;
    ss << std::filesystem::path(source.file_name()).filename().string() << ":" << source.function_name() << ":" << source.line();
    return ss.str();
}

void Logger::log(const std::string &text, LOGLEVEL level, std::source_location const source) {
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
    std::tm *now_tm = std::localtime(&nowTime);
    std::stringstream ss;
    ss << "log_" << std::put_time(now_tm, "%Y-%m-%d") << ".txt";
    std::ofstream file{ss.str(), std::ofstream::app};
    file << "[" << static_cast<char>(level) << "] " << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S") << " | " << sourceToString(source) << " | " << text << std::endl;
}

void log(const std::string &text, LOGLEVEL level, std::source_location const source) {
    Logger::log(text, level, source);
}
