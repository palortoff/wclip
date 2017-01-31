#pragma once

#include <windows.h>
#include <string>
#include "Options.h"

class Clipboard {
    public:
        Clipboard(const Options& options, HWND owner = nullptr);
        ~Clipboard();

        bool isOpen() const noexcept;
        bool Clipboard::copy(const std::string& str) const;

    private:
        Clipboard(const Clipboard&) = delete;
        Clipboard(Clipboard&&) = delete;
        Clipboard& operator=(const Clipboard&) = delete;
        Clipboard& operator=(Clipboard&&) = delete;

        void makeSecret() const;
        void Clipboard::printToConsole(const std::string& str) const;        

        bool _open;
        bool _clipBoardViewerIgnore = false;
        Options _options;
};
