# othello

[![build(Windows)](https://github.com/YTokumaru/othello/actions/workflows/build-windows.yml/badge.svg)](https://github.com/YTokumaru/othello/actions/workflows/build-windows.yml)
[![build(Ubuntu)](https://github.com/YTokumaru/othello/actions/workflows/build-ubuntu.yml/badge.svg)](https://github.com/YTokumaru/othello/actions/workflows/build-ubuntu.yml)
[![build(MacOS)](https://github.com/YTokumaru/othello/actions/workflows/build-macos.yml/badge.svg)](https://github.com/YTokumaru/othello/actions/workflows/build-macos.yml)
[![CodeQL](https://github.com/YTokumaru/othello/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/YTokumaru/othello/actions/workflows/codeql-analysis.yml)
[![codecov](https://codecov.io/gh/YTokumaru/othello/graph/badge.svg?token=IR9HJ42X92)](https://codecov.io/gh/YTokumaru/othello)

## About othello

Simple game of othello, playable from the command line.

<img width="611" alt="Screenshot 2024-05-31 190046" src="https://github.com/YTokumaru/othello/assets/104337837/c60afb57-a8cb-4e5d-928f-de7886417173">

## Build

Build the project with 3 simple steps.
```bash
mkdir build
cmake -DCMAKE_BUILD_TYPE=RELEASE -Bbuild .
cmake --build build
cmake --install build --prefix "Directory to install to"
```
The binary will be available inside the `bin/` directory.
