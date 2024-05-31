# othello

[![build(Windows)](https://github.com/YTokumaru/othello/actions/workflows/build-windows.yml/badge.svg)](https://github.com/YTokumaru/othello/actions/workflows/build-windows.yml)
[![build(Ubuntu)](https://github.com/YTokumaru/othello/actions/workflows/build-ubuntu.yml/badge.svg)](https://github.com/YTokumaru/othello/actions/workflows/build-ubuntu.yml)
[![build(MacOS)](https://github.com/YTokumaru/othello/actions/workflows/build-macos.yml/badge.svg)](https://github.com/YTokumaru/othello/actions/workflows/build-macos.yml)
[![CodeQL](https://github.com/YTokumaru/othello/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/YTokumaru/othello/actions/workflows/codeql-analysis.yml)

## About othello

Simple game of othello, playable from the command line.

## Build

Build the project with 3 simple steps.
```bash
mkdir build
cmake -DCMAKE_BUILD_TYPE=RELEASE -Bbuild .
cmake --build build
cmake --install --prefix "Directory to install to"
```
The binary will be available inside the `bin/` directory.
