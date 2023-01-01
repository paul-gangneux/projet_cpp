#include "view/drawobject/DrawCarcassonne.hpp"
#include <iostream>
#include "geometry/vectors.hpp"

using namespace sf;
using namespace std;

sf::Texture DrawCarcassonne::textures[24];

void DrawCarcassonne::initTextures() {
  for (int i = 0; i < 24; i++) {
    string path = string("./ressource/carcassonne/tile_") + to_string((i + 1)) +
                  string(".jpg");
    bool res = DrawCarcassonne::textures[i].loadFromFile(path);
    if (!res) {
      cout << "Error loading file " << path << endl;
    }
  }
}

Sprite* DrawCarcassonne::createCarcassonneSprite(int type) {
  Sprite* tile = new Sprite();
  tile->setTexture(DrawCarcassonne::textures[type - 1]);
  return tile;
}

DrawCarcassonne::DrawCarcassonne(int type) :
    DrawObject(DrawCarcassonne::createCarcassonneSprite(type)) {
  center = vec2f{100, 100};
  updateTransform();
}

DrawCarcassonne::~DrawCarcassonne() {}

void DrawCarcassonne::draw(sf::RenderTarget* win) const {
  DrawObject::draw(win);
}

void DrawCarcassonne::rotate(float _angle) {
  DrawObject::rotate(_angle);
}

void DrawCarcassonne::setRotation(float _angle) {
  DrawObject::setRotation(_angle);
}