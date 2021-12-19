// Emscripten asynchronous example
// Install Emscripten the usual way and invoke the env vars
// Compile:
// em++ -std=c++17 -pthread -s PTHREAD_POOL_SIZE=16 -s PTHREAD_POOL_SIZE_STRICT=4 -s ALLOW_MEMORY_GROWTH=1 -s WASM=1  ~/Desktop/em_test/hello.cpp -s -o ~/Desktop/em_test/hello.html

//sudo apt-get install gcc-multilib

//
//#include <emscripten/emscripten.h>
 #include <iostream>
// int main(int argc, char** argv){
//   return 0;
// }
// #include <thread>
// #include <string>
// #include <chrono>
// #include <vector>
// #include "./sf2d.h"


#include "./sf2d.h"

//Short cut
typedef sf2d::GL GL;


class MyGame : public sf2d::Game {
public:
  MyGame(std::shared_ptr<sf2d::App> a) : sf2d::Game(a) {
  }
  virtual void init() override {
    //Load Texture
    std::shared_ptr<sf2d::Image32> img = std::make_shared<sf2d::Image32>();
    img->load("./mario.png");
    _tex = std::make_shared<sf2d::Texture2D>(img, true, false, false);
    _tex->setFilter(sf2d::TexFilter::Nearest);

    _quads = std::make_shared<sf2d::QuadBlitter>();
    _quads->setTexture(_tex);
  }
  virtual void update(double delta) override {
    _quads->reset();
    _quads->setQuad(glm::vec2(10,10), app()->viewport(), glm::vec4(1,1,1,1), glm::vec2(64,64));
  }
  virtual void render() override {
    _quads->render(app()->viewport());
  }

private:
  std::shared_ptr<sf2d::Texture2D> _tex = nullptr;
  std::shared_ptr<sf2d::QuadBlitter> _quads = nullptr;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  std::shared_ptr<sf2d::App> a = std::make_shared<sf2d::App>();

  sf2d::Log::info("Hello World.... running the app");

  std::shared_ptr<MyGame> g = std::make_shared<MyGame>(a);
  a->run(g);

  return 0;
}


// #include <GL/gl.h>
// #include <GL/glfw.h>
// #include <GL/glfw.h>

// #include <SDL/SDL.h>
// #include <SDL/SDL_image.h>
// #include <GL/glfw.h>

// typedef void (*renderFunc)();

// void doRenderingLoop(renderFunc doRendering) {
//     emscripten_set_main_loop(doRendering, 0, 1);
// }
// float rotationX, rotationY, rotationZ;
// GLuint textures[1];

// void initGlScene();
// void renderGlScene(double delta);
// //void doRenderingLoop();

// double lastSceneRendered, currentSceneRendered;

// void renderFrame() {
//     currentSceneRendered = glfwGetTime();
//     renderGlScene(currentSceneRendered - lastSceneRendered);
//     lastSceneRendered = currentSceneRendered;
//     glfwSwapBuffers();
// }

int main() {
  //   /* Initialize the library */
  //   if (!glfwInit()) {
  //       printf("Could not initialize library\n");
  //       return -1;
  //   }

  //   /* Create a windowed mode window and its OpenGL context */
  //   if(glfwOpenWindow(640, 480, 0,0,0,0,16,0, GLFW_WINDOW) != GL_TRUE)
  //   {
  //       printf("Could not create OpenGL window\n");
  //       glfwTerminate();
  //       return -1;
  //   }

  //  // initGlScene();
  //  // lastSceneRendered = glfwGetTime();

  // //  doRenderingLoop(&renderFrame);

  //   glfwTerminate();
  //   return 0;
}

// void initTextures() {
//     SDL_Surface *image;
//     if(!(image = IMG_Load("data/qafoo.png"))) {
//         fprintf(stderr, "Could not load texture image: %s\n", IMG_GetError());
//         exit(-1);
//     }

//     glGenTextures(1, textures);
//     glBindTexture(GL_TEXTURE_2D, textures[0]);
//     glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//     glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
//     printf("%ux%u (%u)\n", image->w, image->h, image->format->BytesPerPixel);
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

//     SDL_FreeSurface(image);

//     glEnable(GL_TEXTURE_2D);
// }

// void initGlScene() {
//     int sceneWidth, sceneHeight;

//     initTextures();

//     glClearColor(.41f, 0.71f, 0.4f, 0.0f);
//     glClearDepth(1.0);
//     glDepthFunc(GL_LESS);
//     glEnable(GL_DEPTH_TEST);
//     //glShadeModel(GL_SMOOTH);
    
//     //glMatrixMode(GL_PROJECTION);
//     //glLoadIdentity();
    
//     glfwGetWindowSize(&sceneWidth, &sceneHeight);
//     gluPerspective(45.0f, (GLfloat)sceneWidth / (GLfloat)sceneHeight, 0.1f, 100.0f);

//     //glMatrixMode(GL_MODELVIEW);
// }

// void renderGlScene(double delta) {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glLoadIdentity();

//     // glTranslatef(0.0f,0.0f,-5.0f);
    
//     // glRotatef(rotationX,1.0f,0.0f,0.0f);
//     // glRotatef(rotationY,0.0f,1.0f,0.0f);
//     // glRotatef(rotationZ,0.0f,0.0f,1.0f);

//     glBindTexture(GL_TEXTURE_2D, textures[0]);

//     // glBegin(GL_QUADS);
    
//     // // Front Face (note that the texture's corners have to match the quad's corners)
//     // glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
//     // glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
//     // glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
//     // glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad

//     // // Back Face
//     // glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
//     // glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
//     // glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
//     // glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad

//     // // Top Face
//     // glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
//     // glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
//     // glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
//     // glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
    
//     // // Bottom Face       
//     // glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
//     // glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
//     // glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
//     // glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
    
//     // // Right face
//     // glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
//     // glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
//     // glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
//     // glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
    
//     // // Left Face
//     // glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
//     // glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
//     // glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
//     // glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
    
//     // glEnd();

//     rotationX += delta * 25.0f;
//     rotationY += delta * 25.0f;
//     rotationZ += delta * 25.0f;
// }
// void doRenderingLoop(renderFunc doRendering) {
//     /* Loop until the user closes the window */
//     while (glfwGetWindowParam( GLFW_OPENED ))
//     {
//         doRendering();
//     }
// }

// using namespace std::chrono_literals;
// void task1() {
//   std::cout << "Async task #1 .. sleeping 2s "<<std::endl;
//   std::this_thread::sleep_for(2000ms);
//   std::cout<<"Async task #2 done sleeping." <<std::endl;
// }
// void task2() {
//   std::cout << "Async task #2 .. sleeping 4s "<<std::endl;
//   std::this_thread::sleep_for(4000ms);
//   std::cout<<"Async task #2 done sleeping." <<std::endl;
// }
// int main() {
//   std::cout << "starting main thread " << std::endl;

//   std::cout << "Launching some threads.. " << std::endl;
//   for(int i=0; i<4; ++i){
//    std::thread(task1).detach();
//   }
//   for(int i=0; i<4; ++i){
//    std::thread(task2).detach();
//   }
//   std::cout<<"..done"<<std::endl;

//   return 0;
// }
