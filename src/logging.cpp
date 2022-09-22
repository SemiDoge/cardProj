#include "../inc/logging.h"

void log(std::string msg, logSeverity severity) {
    fmt::v9::text_style style;
    std::string logPrefix = "";

    switch (severity) {
        case logSeverity::ERROR:
        style = fmt::fg(fmt::color::red);
        logPrefix.append("[ERROR]");
        break;
        case logSeverity::INFO:
        style = fmt::fg(fmt::color::blue);
        logPrefix.append("[INFO]");
        break;
        case logSeverity::TRACE:
        style = fmt::fg(fmt::color::purple);
        logPrefix.append("[TRACE]");
        break;
        case logSeverity::DEBUG:
        style = fmt::fg(fmt::color::yellow);
        logPrefix.append("[DEBUG]");
        break;
    }

    fmt::print("{} {}\n", fmt::styled(logPrefix, style), msg);
}