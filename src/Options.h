#pragma once

#include <string>

struct Options {
    static Options create(int argc, char** argv);
    static int print();

    bool valid   = true;
    bool help    = false;
    bool version = false;
    bool stdOut  = false;
    bool secret  = false;

    std::string fileName;
    std::string errorMsg;

    Options& invalid(const std::string& msg);
};
