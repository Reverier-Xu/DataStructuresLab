#include "logs.h"

// getLogHead(): get the specified head of different log levels.
// @level -> LogLevel: the log level.
std::string getLogHead(LogLevel level) {
    switch (level) {
        case MESSAGE:
            return "[\033[36mINFO\033[0m] ";
        case WARNING:
            return "[\033[33mWARNING\033[0m] ";
        case ERROR:
            return "[\033[31mERROR\033[0m] ";
        case FATAL:
            return "[\033[31mFATAL\033[0m] ";
    }
}

void log(LogLevel level, const std::string &head, const std::string &message) {
    std::cout << std::endl;
    std::cout << getLogHead(level) << head;

    // if message is not empty, output it.
    if (!message.empty()) std::cout << ": " << message;
    std::cout << std::endl << std::endl;
}
