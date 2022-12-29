#include "view/drawobject/DrawMeeple.hpp"
#include <iostream>
#include "geometry/vectors.hpp"

using namespace sf;
using namespace std;

sf::Texture DrawMeeple::textures[4];

void DrawMeeple::initTextures() {
  for (int i = 0; i < 4; i++) {
    string path =
        string("./ressource/meeple") + to_string((i + 1)) + string(".png");
    bool res = DrawMeeple::textures[i].loadFromFile(path);
    if (!res) {
      cout << "Error loading file " << path << endl;
    }
  }
}

Sprite* DrawMeeple::createMeepleSprite(int player) {
  Sprite* tile = new Sprite();
  tile->setTexture(DrawMeeple::textures[player]);
  return tile;
}

DrawMeeple::DrawMeeple(int player) :
    DrawObject(DrawMeeple::createMeepleSprite(player)) {
  center = vec2f{50, 50};
  updateTransform();
}

DrawMeeple::~DrawMeeple() {}