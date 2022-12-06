#include "view/Win.hpp"

using namespace sf;

Win::Win(int _width, int _height, const char* name, DrawObject* _object) :
  RenderWindow{VideoMode(_width, _height, 32), name},
  width{_width},
  height{_height},
  rootObject{_object}
{
  setVerticalSyncEnabled(true);
}

Win::Win(int _width, int _height, const char* name) :
  Win(_width, _height, name, nullptr)
{}

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
  Vector2f old_c = getView().getCenter();
  Vector2f new_c = Vector2f(v2.x / 2.0f, v2.y / 2.0f);

  width = v1.x;
  height = v1.y;

  if (rootObject != nullptr) {
    rootObject->move(new_c - old_c);
  }
  setView(View(new_c, v2));
}

void Win::setRootObject(DrawObject* object) {
  rootObject = object;
}
