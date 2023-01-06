#include "view/drawobject/DrawDomino.hpp"
#include <iostream>
#include "geometry/vectors.hpp"

using namespace sf;
using namespace std;

#define POS1 5 + 15
#define POS2 45 + 15
#define POS3 85 + 15
#define POS4 125 + 15
#define POS5 165 + 15

sf::Texture DrawDomino::texture = initTexture();

sf::Texture DrawDomino::initTexture() {
  sf::Texture tex;
  const char path[] = "./ressource/domino.png";
  bool res = tex.loadFromFile(path);
  if (!res) {
    cout << "Error loading file " << path << endl;
  }
  return tex;
}

Sprite* DrawDomino::createDominoSprite() {
  Sprite* tile = new Sprite();
  tile->setTexture(DrawDomino::texture);
  tile->setScale(Vector2f(0.5, 0.5));
  return tile;
}

DrawDomino::DrawDomino(TileDomino* domino) :
    DrawObject(DrawDomino::createDominoSprite()) {
  center = vec2f{100, 100};
  updateTransform();

  for (int i = 0; i < 12; i++) {
    int n = domino->getNumbers()[i];
    sf::Color color;
    if (n == 0) {
      color = sf::Color::Black;
    } else if (n == 1) {
      color = sf::Color::Blue;
    } else if (n == 2) {
      color = sf::Color(0x008800FF);
    } else if (n == 3) {
      color = sf::Color::Magenta;
    } else if (n == 4) {
      color = sf::Color::Red;
    } else {
      color = sf::Color(0x808080FF);
    }
    numbers[i] = new DrawText(to_string(n), color);
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

DrawDomino::~DrawDomino() {
  for (int i = 0; i < 12; i++) {
    delete numbers[i];
  }
}

void DrawDomino::draw(sf::RenderTarget* win) const {
  DrawObject::draw(win);
  for (int i = 0; i < 12; i++) {
    numbers[i]->draw(win);
  }
}

void DrawDomino::rotate(float _angle) {
  DrawObject::rotate(_angle);
  for (int i = 0; i < 12; i++) {
    numbers[i]->rotate(-_angle);
  }
}

void DrawDomino::setRotation(float _angle) {
  DrawObject::setRotation(_angle);
  for (int i = 0; i < 12; i++) {
    numbers[i]->setRotation(-_angle);
  }
}