# Emscripten Test C++ / OpenGL

Emscripten is an api that compiles C++ and OpenGL into javascript for the web. It has its own compiler, and even its own CMake compiler. It packages assets and also generates WASM code for optimal speed. It supports multithreading via webworkers and many more.

This is a simple Emscripen test game engine with C++ / Opengl / SDL and CMake.

Tests <br/>
* Render Speed / WASM
* Threads (-pthread) (compiles to web worker)
* Asset loading.


<img alt="Yes, it works!" src="https://github.com/cacttus/Emscripten_Test/blob/master/ss.png?raw=true" width="400" height="auto">

# How to Run<br/>

## Required Packages 
Linux<br/>
* build-essential
* SDL2
* cmake
* npm
* python
* emscripten
  * https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended
  * Note server.js is configured to look for emsdk at the same level as the Emscripten_Test project (e.g. at ../emsdk)

npm<br/>
* expressjs
* cors

## Running
* Run server.js 'node server.js'. 
  * Note: If threading is enabled then CORS must be enabled in server.js. If you do, the local server needs a certificate to be generated and placed in the same directory as server.js. See OpenSSL certificate generation.
* In your browser type localhost:8080
* For VSCode users: Open the folder in VSCode. F7,F5=compile/run on web (Firefox default), and Ctrl+F7,Ctrl+F5 = Compile/run desktop.
* See .vscode/tasks.json for build string


# TODO

third_party/GLM needs to be a package.
 
