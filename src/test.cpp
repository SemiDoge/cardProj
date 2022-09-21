#define FMT_HEADER_ONLY

#include <iostream>
#include <fmt/format.h>
#include <fmt/color.h>
#include <cxxopts.hpp>
#include <SDL/SDL.h>

void printVersion();
cxxopts::ParseResult setUpWorkflow(int argc, char** argv, cxxopts::Options & options);

int main (int argc, char** argv) {
    cxxopts::Options options("test", "This is a starter CMake/Conan C++ project.\n");

    auto optRes = setUpWorkflow(argc, argv, options);

    fmt::print("{}",
            fmt::styled("This is a starter CMake/Conan C++ project.\n",
            fmt::fg(fmt::color::green)));

    
    return EXIT_SUCCESS;
}

cxxopts::ParseResult setUpWorkflow(int argc, char** argv, cxxopts::Options & options) {

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
    fmt::print("TEST VERSION {}\n", fmt::styled("0.1", fmt::fg(fmt::color::red)));
}