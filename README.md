# wclip - Windows CLI clipping tool

wclip is a command line tool to copy data to the windows clipboard. It can take data from a file or stdin, e.g. using the pipe.

wclip adds the ``--secret`` option to tell [ClipMate](http://www.thornsoft.com/clipmate7.htm), [AceText](https://www.acetext.com/) and other clipboard viewers not to capture the copied data. This way the clipboard history can be kept free from passwords copied from a password manager like [password-store](https://www.passwordstore.org/).

wclip is used in [pass-extension-wclip](https://github.com/palortoff/pass-extension-wclip), an extension for [password-store](https://www.passwordstore.org/).

## Usage

```
wclip - command line interface to the windows clipboard

usage: wclip [option] [file]

Reads from standard in when no file is given or a file and makes the data available in the clipboard.

   -v, --version    show version information
   -h, --help       show usage information
   -o, --out        prints the copied data to stdout
   -s, --secret     hides the copied data from clipboard history tools
                    (generally used for passwords)
```
## Example
```
pass some/secret/password | wclip --secret
```
Copies the password to the clipboard without having it stored in the clipboard history.

## How to build

wclip is build with [CMake](https://cmake.org/) and [Visual Studio](https://www.visualstudio.com/de/), preferably using the command line.

### Environment setup

Open a ``VS2015 x64 Native Tools Command Prompt`` and change to your working directory

Add cmake to the PATH if necessary.

### Get the sources

Clone the wclip repository

```
git clone  https://github.com/palortoff/wclip.git
```

Enter the project folder

```
cd wclip
```

### Run CMake

Create and enter the build folder

```
mkdir build
cd build
```

Create NMake make files for the Release configuration:

```
cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release ..
```

or the Debug configuration:

```
cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
```

Or create a Visual Studio solution file:

```
cmake -G "Visual Studio 12 2013 Win64" ..
```

### Building the binary

To compile wclip now run:

```
nmake
```

To build with Visual Studio open the ``wclip.sln`` solution file and build in Release or Debug configuration.


The binary will be written to

```
<repository root>/dist/release
```
or
```
<repository root>/dist/debug
```

## Testing

The wclip tests are written with [Bats](https://github.com/sstephenson/bats) and use the wclip.exe in Release configuration from ``dist/release``.

Bats requires a bash to run
Open a bash shell (like the git bash for windows) in the wclip repository root. If you don't have bats already configured, run bats like this:

```
<path to bats repository root>/libexec/bats tests
```

This tests the complete wclip functionality except for the ``--secret`` parameter, as this is not possible with simple shell capabilities.

## Install

As windows does not have a designated location to put binaries that are available in the path, simply copy the ``wclip.exe`` from ``dist/release`` to a location available in the path. Wclip is linked statically so there is no need to install a runtime or other libraries.

## Acknowledgements / Links

wclip is based on this [xlip](https://linux.die.net/man/1/xclip) port to windows:
https://gist.github.com/Rapptz/9664773178da1bc397cf

[Ignoring Clipboard Updates with the CF_CLIPBOARD_VIEWER_IGNORE Clipboard Format](http://www.clipboardextender.com/developing-clipboard-aware-programs-for-windows/ignoring-clipboard-updates-with-the-cf_clipboard_viewer_ignore-clipboard-format)
