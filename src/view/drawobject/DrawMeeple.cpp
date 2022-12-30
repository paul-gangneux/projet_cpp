#include "view/drawobject/DrawMeeple.hpp"
#include <iostream>
#include "geometry/vectors.hpp"

using namespace sf;
using namespace std;

sf::Texture DrawMeeple::potentialMeepTex;
sf::Texture DrawMeeple::textures[4];

void DrawMeeple::initTextures() {
  string path = string("./ressource/potential_meeple.png");
  bool res = DrawMeeple::potentialMeepTex.loadFromFile(path);
  if (!res) {
    cout << "Error loading file " << path << endl;
  }

  for (int i = 0; i < 4; i++) {
    path = string("./ressource/meeple") + to_string((i + 1)) + string(".png");
    res = DrawMeeple::textures[i].loadFromFile(path);
    if (!res) {
      cout << "Error loading file " << path << endl;
    }
  }
}

Sprite* DrawMeeple::createMeepleSprite(int player) {
  Sprite* tile = new Sprite();
  if (player == -1) {
    tile->setTexture(DrawMeeple::potentialMeepTex);
  } else {
    tile->setTexture(DrawMeeple::textures[player]);
  }
  return tile;
}

DrawMeeple::DrawMeeple(int player) :
    DrawObject(DrawMeeple::createMeepleSprite(player)) {
  setCenter(50, 50);
}

DrawMeeple::~DrawMeeple() {}