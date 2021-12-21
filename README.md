# Emscripten Test C++ / OpenGL

Emscripten is a neat tool that compiles C++ and OpenGL into javascript for the web. It has its own compiler, and even its own CMake compiler. It packages assets and also generates WASM code for optimal speed. It even supports multithreading via webworkers.

This is a simple Emscripen test game engine with C++ / Opengl / SDL / CMake. The goal of this project is to test out the feasibility of emscripten as a commercial game engine.

Tests <br/>
* Render Speed / WASM
* Threads (-pthread) (compiles to web worker)
* Dynamic asset loading.

# How to Run<br/>

Run the server.js via node. (for CORS local server needs a certificate to be generated see OpenSSL certificate generation).

src/main.cpp has the terminal build string for plain em++. There is also a build string in the CMake file for the cmake version (may not be up to date).

pkg install<br/>
* build-essential
* SDL2
* cmake
* python
* emscripten (git)
  * https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended
  * Note server.js is configured to look for emsdk at the same level as the Emscripten_Test project (e.g. ..)

npm install<br/>
* expressjs
* cors


* VSCode users F7,F5=compile/run on web (Firefox default), and Ctrl+F7,Ctrl+F5 = Compile/run desktop.

* See .vscode/tasks.json



# Image
![Image](https://github.com/cacttus/Emscripten_Test/blob/master/ss.png?raw=true)


# TODO

third_party/GLM needs to be a package.
 
