/*

# This is the current working build command for emscripten WITH THREADS that means the CORS require-corp and same-origin must be sent.
mkdir -p ~/Desktop/em_test/build && EMCC_DEBUG=2; em++ -g -g4 -std=c++17 -pthread -I~/Desktop/em_test/third_party -s PTHREAD_POOL_SIZE=16 -s PTHREAD_POOL_SIZE_STRICT=4 -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s FULL_ES3=1 -s USE_SDL=2 -s EXPORT_ES6=1 ~/Desktop/em_test/src/main.cpp ~/Desktop/em_test/src/lodepng.cpp -s -o ~/Desktop/em_test/build/hello.html --source-map-base=/build/ --preload-file ~/Desktop/em_test/assets/

# Same thing without threading
mkdir -p ~/Desktop/em_test/build && EMCC_DEBUG=2; em++ -g -g4 -std=c++17 -I~/Desktop/em_test/third_party -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s FULL_ES3=1 -s USE_SDL=2 -s EXPORT_ES6=1 ~/Desktop/em_test/src/main.cpp ~/Desktop/em_test/src/lodepng.cpp -s -o ~/Desktop/em_test/build/hello.html --source-map-base=/build/ --preload-file ~/Desktop/em_test/assets/


*/

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
    std::cout << "cur path=" << std::filesystem::current_path() << std::endl;
    for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
      std::cout <<"  "<< entry.path() << std::endl;
    }

    img->load("assets/mario.png");
    _tex = std::make_shared<sf2d::Texture2D>(img, true, false, false);
    _tex->setFilter(sf2d::TexFilter::Nearest);

    _quads = std::make_shared<sf2d::QuadBlitter>();
    _quads->setTexture(_tex);
  }
  virtual void update(double delta) override {
    _quads->reset();
    _quads->setQuad(glm::vec2(10, 10), app()->viewport(), glm::vec4(1, 1, 1, 1), glm::vec2(64, 64));
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
