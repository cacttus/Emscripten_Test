/*
See readme for compile instructions
*/

#include "./sf2d.h"

//Short cut
typedef sf2d::GL GL;

class MyGame : public sf2d::Game {
public:
  MyGame(sf2d::App* a) : sf2d::Game(a) {
  }
  virtual ~MyGame() override {}
  virtual void init() override {
    BRLogInfo("Init Game..");
    
    //Some debugging here...
    std::cout << "cur path=" << std::filesystem::current_path() << std::endl;
    for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
      std::cout << "  " << entry.path() << std::endl;
    }

    //Load Texture
    std::shared_ptr<sf2d::Image32> img = std::make_shared<sf2d::Image32>();
    img->load("./assets/mario.png");
    _tex = std::make_shared<sf2d::Texture2D>(img, true, false, false);
    _tex->setFilter(sf2d::TexFilter::Nearest);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glDisable(GL_DEPTH_TEST);

    if (this->app()->_emscripten) {
      _quads = std::make_shared<sf2d::QuadBlitterES3>(2048);
    }
    else {
      _quads = std::make_shared<sf2d::QuadBlitterGL4>(8192);
    }
    _quads->setTexture(_tex);
    BRLogInfo("Init Game Success.");
  }
  virtual void update(double delta) override {
    _quads->reset();
    _quads->setQuad(_marioPos, app()->viewport(), glm::vec4(1, 1, 1, 1), _marioPos + glm::vec2(50, 70));
    if(sf2d::Gu::getGlobalInput()->pressOrDown(SDL_SCANCODE_W) || sf2d::Gu::getGlobalInput()->pressOrDown(SDL_SCANCODE_UP)){
      _marioPos.y-=30 * delta;
    }
    if(sf2d::Gu::getGlobalInput()->pressOrDown(SDL_SCANCODE_S) || sf2d::Gu::getGlobalInput()->pressOrDown(SDL_SCANCODE_DOWN)){
      _marioPos.y+=30 * delta;
    }
    if(sf2d::Gu::getGlobalInput()->pressOrDown(SDL_SCANCODE_A) || sf2d::Gu::getGlobalInput()->pressOrDown(SDL_SCANCODE_LEFT)){
      _marioPos.x-=30 * delta;
    }
    if(sf2d::Gu::getGlobalInput()->pressOrDown(SDL_SCANCODE_D) || sf2d::Gu::getGlobalInput()->pressOrDown(SDL_SCANCODE_RIGHT)){
      _marioPos.x+=30 * delta;
    }
  }
  virtual void render() override {
    _quads->render(app()->viewport());
  }

private:
  std::shared_ptr<sf2d::Texture2D> _tex = nullptr;
  std::shared_ptr<sf2d::IQuadBlitter> _quads = nullptr;
  glm::vec2 _marioPos=glm::vec2(10,10);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static sf2d::App* a = nullptr;
static sf2d::Game* g = nullptr;
int main(int argc, char** argv) {
  sf2d::Log::info("Hello World.... running the app");

  a = new sf2d::App();
  g = new MyGame(a);

  a->run(g);

#ifndef __EMSCRIPTEN__
  //Horrendous!
  delete a;
  delete g;
#endif
  return 0;
}

#ifdef __EMSCRIPTEN__
namespace sf2d {

void emscripten_renderloop(void* arg) {
  sf2d::App* pApp = (sf2d::App*)arg;
  if (pApp) {
    pApp->renderLoop();
  }
  else {
    BRLogError("Emscripten render loop argument 'app' not supplied.");
  }
}

}  // namespace sf2d

#endif
