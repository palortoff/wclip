#include "Options.h"

#include <vector>
#include <algorithm>

#include <iostream>

namespace {
    bool matches(
        const std::string& param,
        const std::string& longName,
        const std::string& shortName){
            if (param == "--" + longName) return true;

            if (param.c_str()[0] == '-' && param.c_str()[1] != '-') {
                auto pos = param.find(shortName);
                return pos != std::string::npos;
            }
            return false;
    }

    std::string allowedShortParams = "sovh";

    bool shortParamListContainsUnknows(const std::string& param){
        if (param.length() < 2) return false;
        if (param.c_str()[0] != '-') return false;
        if (param.c_str()[1] == '-') return false;

        for (int i = 1; i < param.length(); ++i){
            if (allowedShortParams.find(param.c_str()[i]) == std::string::npos){
                return true;
            }
        }
        return false;
    }

    bool startsWithDash(const std::string &param){
        return param.find("-") == 0;
    }
}

Options Options::create(int argc, char** argv) {
    Options o;
    std::vector<std::string> args{ argv, argv + argc };

    for(auto it = ++args.cbegin(); it != args.cend(); ++it) {
        const std::string param = *it;
        bool paramUsed = false;
        if (matches(param, "help", "h"))    { o.help    = true; paramUsed = true; }
        if (matches(param, "version", "v")) { o.version = true; paramUsed = true; }
        if (matches(param, "out", "o"))     { o.stdOut  = true; paramUsed = true; }
        if (matches(param, "secret", "s"))  { o.secret  = true; paramUsed = true; }

        if (shortParamListContainsUnknows(param)){
            return o.invalid("invalid option: " + param);
        }

        if (paramUsed) continue;

        if (startsWithDash(param)) {
            return o.invalid("invalid option: " + param);
        }

        if (o.fileName.length()) return o.invalid("cannot copy multiple files");
        o.fileName = param;
    }

    return o;
}

int Options::print(){
    std::cout <<
        "wclip - command line interface to the windows clipboard\n\n"
        "usage: wclip [option] [file]\n\n"
        "Reads from standard in when no file is given or a file and "
        "makes the data available in the clipboard.\n\n"
        "   -v, --version    show version information\n"
        "   -h, --help       show usage information\n"
        "   -o, --out        prints the copied data to stdout\n"
        "   -s, --secret     hides the copied data from clipboard history tools\n"
        "                    (generally used for passwords)\n\n";
    return EXIT_SUCCESS;
}

Options& Options::invalid(const std::string& msg) {
    errorMsg = msg;
    valid = false;
    return *this;
}
