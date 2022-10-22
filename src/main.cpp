#define FMT_HEADER_ONLY

#include <iostream>
#include <cxxopts.hpp>

#include "../inc/cardproj.hpp"

void printVersion();
cxxopts::ParseResult setUpWorkflow(int argc, char** argv, cxxopts::Options & options);

int main (int argc, char** argv) {
    cxxopts::Options options("cardproj", 
        "This project is a demonstration of C++ and SDL2. Clicking on the stack of cards on the left of the window will generate a random 'draw' of two playing cards.\n");
    auto optRes = setUpWorkflow(argc, argv, options);
    CPWindow appWindow(1240, 600);
    

    Logger::log("Starting SDL object...", logSeverity::INFO);
    auto ret = appWindow.OnExecute();
    
    
    Logger::log(fmt::format("OnExecute() returned {} at frame#{}", ret, appWindow.iFrame), logSeverity::INFO);
    return ret;
}

cxxopts::ParseResult setUpWorkflow(int argc, char** argv, cxxopts::Options & options) {

    options.add_options()
        ("v,version", "PRINT program version")
        ("h,help", "PRINT help text")
        ("l,log", "Allow debug logging")
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        fmt::print("{}", options.help());
        exit(EXIT_SUCCESS);
    }

    if (result.count("version")) {
        printVersion();
        exit(EXIT_SUCCESS);
    }

    if (result.count("log")) {
        Logger::setAllowedToPrint(true);
    } else {
        Logger::setAllowedToPrint(false);
    }

    return result;
}

void printVersion() {
    fmt::print("cardproj VERSION {}\n", fmt::styled("0.92", fmt::fg(fmt::color::orange)));
}
