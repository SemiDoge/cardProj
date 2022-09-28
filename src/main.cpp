#define FMT_HEADER_ONLY

#include <iostream>
#include <cxxopts.hpp>

#include "../inc/cardproj.h"

void printVersion();
cxxopts::ParseResult setUpWorkflow(int argc, char** argv, cxxopts::Options & options);

int main (int argc, char** argv) {
    cxxopts::Options options("cardproj", "This simple program will eventually render two playing cards to the screen.\n");
    auto optRes = setUpWorkflow(argc, argv, options);
    CPWindow appWindow(1240, 600);
    

    log("Starting SDL object...", logSeverity::INFO);
    auto ret = appWindow.OnExecute();
    
    log(fmt::format("OnExecute() returned {} at frame#{}", ret, appWindow.iFrame), logSeverity::INFO);
    return ret;
}

cxxopts::ParseResult setUpWorkflow(int argc, char** argv, cxxopts::Options & options) {

    //TODO: add an option to display/hide log output.
    options.add_options()
        ("v,version", "PRINT program version")
        ("h,help", "PRINT help text")
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

    return result;
}

void printVersion() {
    fmt::print("cardproj VERSION {}\n", fmt::styled("0.3", fmt::fg(fmt::color::orange)));
}