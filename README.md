# Emscripten Test C++ / OpenGL

Emscripten is a neat tool that compiles C++ and OpenGL into javascript for the web. It has its own compiler, and even its own CMake compiler. It packages assets and also generates WASM code for optimal speed. It even supports multithreading via webworkers.

This is a simple Emscripen test game engine with C++ / Opengl / SDL / CMake. The goal of this project is to test out the feasibility of emscripten as a commercial game engine.

Tests <br/>
* Render Speed / WASM
* Threads (-pthread) (compiles to web worker)
* Dynamic asset loading.

# Comments

So I kicked this project too early to Github thinking the test was complete. It actually wasn't so this is a more working version. 

This runs ES3 (emulation) in the browser and GL4.3 on the desktop. If you import the keybindings.json into VSCode the project is set up to run as: F7,F5=compile/run on web, and Ctrl+F7,Ctrl+F5 = Compile/run desktop.

# How to Run<br/>

Note, you have to run this via a server and hit localhost (You can't just click on the outupt HTML file). If CORS is enabled in the server.js (cross-origin .. ) your local server needs a certificate to be generated before it will allow these cross origin headers (see OpenSSL certificate generation).

src/main.cpp has the terminal build string for plain em++. There is also a build string in the CMake file for the cmake version (may not be up to date).

## 1. Install

pkg install<br/>
* build-essential
* SDL2
* cmake
* python
* emscripten - from git.
    * https://emscripten.org/docs/getting_started/downloads.html

npm install<br/>
* expressjs
* cors

## 2. bash
CD to em_test and run in terminal.

Threaded
mkdir -p ./build && EMCC_DEBUG=2; em++ -g -gsource-map -std=c++17 -pthread -I./third_party -s PTHREAD_POOL_SIZE=16 -s PTHREAD_POOL_SIZE_STRICT=4 -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s FULL_ES3=1 -s USE_SDL=2 -s EXPORT_ES6=1 ./src/main.cpp ./src/lodepng.cpp -s -o ./build/hello.html --source-map-base=/build/ --preload-file ./assets/

Non-Threaded
mkdir -p ./build && EMCC_DEBUG=2; em++ -g -gsource-map -std=c++17 -I./third_party -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s FULL_ES3=1 -s USE_SDL=2 -s EXPORT_ES6=1 ./src/main.cpp ./src/lodepng.cpp -s -o ./build/hello.html --source-map-base=/build/ --preload-file ./assets/

# Problems

1. The express.js server instance doesn't handle queries the right way. It doesn't look very nice. It runs locally over an instance of CORS.

# TODO

third_party/GLM needs to be a package.
 
