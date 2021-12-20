#ifndef _FINAL_LOGS_H_
#define _FINAL_LOGS_H_

#include <iostream>

// LogLevel:
// enum type to describe the log level.
enum LogLevel {
    MESSAGE, // debug message can use this
    WARNING, // illegal but may calculate
    ERROR,   // can't calculate
    FATAL    // this is something wrong with the program,
             // maybe a bug or a operating system error.
             // if you logged FATAL, then you should call exit(1) to terminate the program immediately.
};

// getLogHead(): get a cute head from parameter @level -> LogLevel.
// @level -> LogLevel: the log level.
std::string getLogHead(LogLevel level);

// log(): log the message with severity level.
// @level -> LogLevel: the message's severity level.
// @head -> std::string: the info head of what you want to log.
// @message -> std::string: the info body. if you want to log the message exactly, put the body at here.
//                          do not put a lot of message in head.
void log(LogLevel level, const std::string &head, const std::string &message = "");

#endif //_FINAL_LOGS_H_
