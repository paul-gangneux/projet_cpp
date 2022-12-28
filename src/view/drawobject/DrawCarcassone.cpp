#include "view/drawobject/DrawCarcassone.hpp"
#include <iostream>
#include "geometry/vectors.hpp"

using namespace sf;
using namespace std;

sf::Texture DrawCarcassone::textures[24];

void DrawCarcassone::initTextures() {
  for (int i = 0; i < 24; i++) {
    string path = string("./ressource/carcassone/tile_") + to_string((i + 1)) +
                  string(".jpg");
    bool res = DrawCarcassone::textures[i].loadFromFile(path);
    if (!res) {
      cout << "Error loading file " << path << endl;
    }
  }
}

Sprite* DrawCarcassone::createCarcassoneSprite(int type) {
  Sprite* tile = new Sprite();
  tile->setTexture(DrawCarcassone::textures[type - 1]);
  tile->setScale(Vector2f(0.5, 0.5));
  return tile;
}

DrawCarcassone::DrawCarcassone(int type) :
    DrawObject(DrawCarcassone::createCarcassoneSprite(type)) {
  center = vec2f{100, 100};
  updateTransform();
  // todo: meeples
}

DrawCarcassone::~DrawCarcassone() {
  // todo: meeples
}

void DrawCarcassone::draw(sf::RenderTarget* win) const {
  DrawObject::draw(win);
  // todo: meeples
}

void DrawCarcassone::rotate(float _angle) {
  DrawObject::rotate(_angle);
  // todo: meeples
}

void DrawCarcassone::setRotation(float _angle) {
  DrawObject::setRotation(_angle);
  // todo: meeples
}