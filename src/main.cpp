#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

#include "version.h"
#include "Clipboard.h"
#include "Options.h"

namespace{
    int success(bool s){
        return s ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    int version()
    {
        std::cout << "wclip version "<< WCLIP_VERSION_MAJOR << "." << WCLIP_VERSION_MINOR << "\n";
        return EXIT_SUCCESS;
    }

    int error(const std::string& str)
    {
        std::cerr << "wclip - error: " << str << '\n';
        return EXIT_FAILURE;
    }

    int copyFromStdIn(const Clipboard& clip)
    {
        std::ostringstream stream;
        for (std::string line; std::getline(std::cin, line); ) {
            stream << line;
        }
        return success(clip.copy(stream.str()));
    }

    int copyFromFile(const Clipboard& clip, const std::string& filename)
    {
        if (filename.empty()) return error("no input file given");
        std::ifstream in(filename);
        if (!in.is_open()) return error("unable to open file " + filename);
        std::ostringstream stream;
        stream << in.rdbuf();
        return success(clip.copy(stream.str()));
    }
}

int main(int argc, char** argv)
{
    auto options = Options::create(argc, argv);

    if (!options.valid) return error(options.errorMsg);
    if (options.help) return Options::print();
    if (options.version) return version();

    Clipboard clip(options);
    if (!clip.isOpen()) {
        return error("unable to open Clipboard");
    }

    if (options.fileName.length() == 0) {
        return copyFromStdIn(clip);
    }
    else {
        return copyFromFile(clip, options.fileName);
    }
}
