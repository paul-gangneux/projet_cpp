#include "view/DrawDomino.hpp"
#include "geometry/vectors.hpp"
#include <iostream>

using namespace sf;
using namespace std;

#define POS1 0
#define POS2 45
#define POS3 85
#define POS4 125
#define POS5 165

sf::Texture initTexture() {
  sf::Texture tex;
  const char path[] = "./ressource/domino.png";
  bool res = tex.loadFromFile(path);
  if (!res) {
    cout << "Error loading file " << path << endl;
  }
  return tex;
}

sf::Texture DrawDomino::texture = initTexture();

Sprite* DrawDomino::createDominoSprite() {
  Sprite* tile = new Sprite();
  tile->setTexture(DrawDomino::texture);
  tile->setScale(Vector2f(0.5, 0.5));
  return tile;
}

DrawDomino::DrawDomino() :
  DrawObject(DrawDomino::createDominoSprite()) {

  center = vec2f{100, 100};
  updateTransform();

  for (int i = 0; i < 12; i++) {
    numbers[i] = new DrawText(to_string(i), sf::Color::Blue);
    numbers[i]->setParent(this);
  }

  // it works for now
  numbers[0]->move(POS2, POS1);
  numbers[1]->move(POS3, POS1);
  numbers[2]->move(POS4, POS1);

  numbers[3]->move(POS5, POS2);
  numbers[4]->move(POS5, POS3);
  numbers[5]->move(POS5, POS4);

  numbers[6]->move(POS4, POS5);
  numbers[7]->move(POS3, POS5);
  numbers[8]->move(POS2, POS5);

  numbers[9]->move(POS1, POS4);
  numbers[10]->move(POS1, POS3);
  numbers[11]->move(POS1, POS2);
}

DrawDomino::~DrawDomino()
{
  for (int i = 0; i < 12; i++) {
    delete numbers[i];
  }
}

void DrawDomino::draw(sf::RenderTarget& win) const {
  DrawObject::draw(win);
  for (int i = 0; i < 12; i++) {
    numbers[i]->draw(win);
  }
}

void DrawDomino::rotate(float _angle) {
  DrawObject::rotate(_angle);
  for (int i = 0; i < 12; i++) {
    numbers[i]->rotate(-_angle, 15, 15);
  }
}