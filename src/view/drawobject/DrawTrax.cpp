#include "view/drawobject/DrawTrax.hpp"

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

Texture DrawTrax::texture1 = initTexture("./ressource/trax_tile1.png");
Texture DrawTrax::texture2 = initTexture("./ressource/trax_tile2.png");

Sprite* DrawTrax::createSprite(int type, bool transparent) {
  Sprite* tile = new Sprite();
  if (type == 0) {
    tile->setTexture(DrawTrax::texture1);
  }
  else {
    tile->setTexture(DrawTrax::texture2);
  }
  tile->setScale(Vector2f(0.5, 0.5));
  if (transparent) {
    tile->setColor(sf::Color(255, 255, 255, 128));
  }
  return tile;
}

DrawTrax::DrawTrax(int type, bool transparent) :
  DrawObject(DrawTrax::createSprite(type, transparent))
{
  center = vec2f{100, 100};
  updateTransform();
}

DrawTrax::~DrawTrax() {}