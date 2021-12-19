# Emscripten Test C++ / OpenGL

Emscripten is a neat tool that compiles C++ and OpenGL into javascript for the web. It has its own compiler, and even its own CMake compiler. It packages assets and also generates WASM code for optimal speed. It even supports multithreading via webworkers.

This is a simple Emscripen test game engine with C++ / Opengl / SDL / CMake / Linux. The goal of this project is to test out the feasibility of emscripten as a commercial game engine.

Tests <br/>
* Render Speed / WASM
* Threads (-pthread) (compiles to web worker)
* Dynamic asset loading.
* CORS 

# Results

I wrote this guy several months ago but abandoned it for just a few reasons. Frankly, I had trouble with assets. Everything else panned out fine.

The biggest problem was asset loading. Especially for a game engine, we need to dynamically create and modify data very quickly meaning disk I/O and you can't do that easily on the web. The local assets for this engine were created through a package.

One way around this is to keep user's assets in a database. That's a whole nother spectrum of complexity to dive into. Emscripten is really cool. I might pick this project back up in the future to see if we can get around some of these limitations.

# How to Run<br/>


Note, you have to run this via a server and hit localhost (You can't just click on the outupt HTML file). Due to CORS your local server needs a certificate to be generated before it will allow these cross origin headers (see OpenSSL certificate generation).

src/main.cpp has the terminal build string for plain em++. There is also a build string in the CMake file for the cmake version (may not be up to date).

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
 
