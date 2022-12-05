#include "view/DrawTrex.hpp"

using namespace sf;
using namespace std;

Texture initTexture(const char* path) {
  Texture tex;
  bool res = tex.loadFromFile(path);
  if (!res) {
    cout << "Error loading file " << path << endl;
  }
  return tex;
}

Texture DrawTrex::texture1 = initTexture("./ressource/trax_tile1.png");
Texture DrawTrex::texture2 = initTexture("./ressource/trax_tile2.png");

Sprite* DrawTrex::createSprite(int type) {
  Sprite* tile = new Sprite();
  if (type == 1) {
    tile->setTexture(DrawTrex::texture1);
  }
  else {
    tile->setTexture(DrawTrex::texture2);
  }
  tile->setScale(Vector2f(0.5, 0.5));
  return tile;
}

DrawTrex::DrawTrex(int type) :
  DrawObject(DrawTrex::createSprite(type)) {
  center = vec2f{100, 100};
  updateTransform();
}

DrawTrex::~DrawTrex() {}