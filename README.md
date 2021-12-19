# Emscripten Test C++ / OpenGL

Emscripten is a neat tool that compiles C++ and OpenGL into javascript or wasm for the web.

This is a simple Emscripen test engine with C++ / Opengl / CMake / Linux. The goal of this project is to test out the feasibility of emscripten as a commercial game engine.

Tests <br/>
* Render Speed / WASM
* Threads (-pthread) (compiles to web worker)
* Asset creation.
* Asset Compression. 
* Dynamic asset loading.
* CORS 

# Results

1. I wrote this guy several months ago but abandoned it for several reasons. It is not the best way to create a game engine. The biggest problem with (not emscripten but the web) was asset loading. Especially for a game engine, we need to dynamically create and modify data very quickly meaning disk I/O and you can't do that easily on the web. This is an even bigger issue with asset creation which essentially would benefit from direct IO. One way around this is to keep user's assets in a database. That's a whole nother spectrum of complexity to dive into. Emscripten is really cool though. I might pick this project back up in the future.

# How to Run<br/>

Note the app needs a local server certificate to be generated before it will work.
src/main.cpp has the terminal build string

pkg install<br/>
* cmake
* emscripten

npm install<br/>
* expressjs
* cors

# Problems

1. The express.js server instance doesn't handle queries the right way. It doesn't look very nice. It runs locally over an instance of CORS.

# TODO

third_party/GLM needs to be a package.
 
