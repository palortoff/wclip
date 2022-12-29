#include "Clipboard.h"

#include <iostream>

namespace {
    void clear(){
        EmptyClipboard();
    }
}

Clipboard::Clipboard(const Options& options, HWND owner)
    : _open(!!OpenClipboard(owner))
    , _options(options)
{
}

Clipboard::~Clipboard()
{
    if (_open) CloseClipboard();
}

bool Clipboard::isOpen() const noexcept
{
    return _open;
}

void Clipboard::makeSecret() const {
    if (_options.secret) {
        UINT CF_CLIPBOARD_VIEWER_IGNORE = RegisterClipboardFormat("Clipboard Viewer Ignore");
        SetClipboardData(CF_CLIPBOARD_VIEWER_IGNORE, nullptr);
        UINT CF_CLIPBOARD_MONITOR_EXLUDE = RegisterClipboardFormat("ExcludeClipboardContentFromMonitorProcessing");
        SetClipboardData(CF_CLIPBOARD_MONITOR_EXLUDE, nullptr);
    }
}

void Clipboard::printToConsole(const std::string& str) const {
    if (_options.stdOut) std::cout << str << "\n";
}

bool Clipboard::copy(const std::string& str) const
{
    if (_open) {
        clear();
        HGLOBAL buffer = GlobalAlloc(GMEM_DDESHARE, str.size() + 1);
        if (buffer) {
            memcpy(GlobalLock(buffer), str.c_str(), str.size() + 1);
            GlobalUnlock(buffer);
            makeSecret();
            auto success =  SetClipboardData(CF_TEXT, buffer) != nullptr;
            GlobalFree(buffer);
            printToConsole(str);
            return success;
        }
    }
    return false;
}
