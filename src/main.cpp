/*
See readme for compile instructions
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
      std::cout << "  " << entry.path() << std::endl;
    }

    img->load("./assets/mario.png");
    std::cout << "hi" << std::endl;
    std::cout << "hi" << std::endl;
    _tex = std::make_shared<sf2d::Texture2D>(img, true, false, false);
    _tex->setFilter(sf2d::TexFilter::Nearest);

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    if (this->app()->_emscripten) {
      _quads = std::make_shared<sf2d::QuadBlitterES3>();
    }
    else {
      _quads = std::make_shared<sf2d::QuadBlitterGL4>();
    }
    _quads->setTexture(_tex);
  }
  virtual void update(double delta) override {
    _quads->reset();
    _quads->setQuad(glm::vec2(0, 0), app()->viewport(), glm::vec4(1, 1, 1, 1), glm::vec2(.2, .2));
    _quads->setQuad(glm::vec2(10, 10), app()->viewport(), glm::vec4(1, 1, 1, 1), glm::vec2(2, 2));
    _quads->setQuad(glm::vec2(-10, -10), app()->viewport(), glm::vec4(1, 1, 1, 1), glm::vec2(2, 2));
    _quads->setQuad(glm::vec2(-10, 10), app()->viewport(), glm::vec4(1, 1, 1, 1), glm::vec2(.2, .2));
  }
  virtual void render() override {
    _quads->render(app()->viewport());
  }

private:
  std::shared_ptr<sf2d::Texture2D> _tex = nullptr;
  std::shared_ptr<sf2d::IQuadBlitter> _quads = nullptr;
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  sf2d::Log::info("Hello World.... running the app");
  std::shared_ptr<sf2d::App> a = std::make_shared<sf2d::App>();
  std::shared_ptr<MyGame> g = std::make_shared<MyGame>(a);
  a->run(g);

  return 0;
}
