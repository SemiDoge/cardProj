#ifndef LOGGING_H
#define LOGGING_H


#include <fmt/format.h>
#include <fmt/color.h>



enum logSeverity {
    ERROR = -1,
    INFO,
    TRACE,
    DEBUG,
};

void log(std::string msg, logSeverity sever);

#endif