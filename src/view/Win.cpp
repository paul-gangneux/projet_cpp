#include "view/Win.hpp"

using namespace sf;

Win::Win(int _width, int _height, const char* name) :
  RenderWindow{VideoMode(_width, _height, 32), name},
  width{_width},
  height{_height} {}

Win::~Win() {
  close();
}

int Win::getWidth() const {
  return width;
}

int Win::getHeight() const {
  return height;
}

void Win::onResize() {
  RenderWindow::onResize();
  
  Vector2u v1 = getSize();
  Vector2f v2(v1.x, v1.y);
  Vector2f c = getView().getCenter();
  c = Vector2f(v2.x / 2.0f, v2.y / 2.0f);

  width = v1.x;
  height = v1.y;

  setView(View(c, v2));
}