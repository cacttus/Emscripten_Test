# Emscripten Test C++ / OpenGL

Emscripten is a neat tool that compiles C++ and OpenGL into javascript or wasm for the web.

This is a simple Emscripen test engine with C++ / Opengl / CMake / Linux.

Tests <br/>
* Render Speed in WASM
* Threads (-pthread)
* CORS  

# Problems
The express.js server instance doesn't handle queries the right way. It doesn't look very nice. It runs locally over an instance of CORS.

# How to Run<br/>

Note the app needs a local server certificate to be generated before it will work.
src/main.cpp has the terminal build string

pkg install<br/>
* cmake
* emscripten

npm install<br/>
* expressjs
* cors


# TODO

third_party/GLM needs to be a package.
 
