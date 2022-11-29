#include "view/DrawObject.hpp"

using namespace std;
using namespace sf;

DrawObject::DrawObject() :
  parent{nullptr},
  dr_ptr{nullptr},
  tr_ptr{nullptr},
  trans{Transform::Identity},
  position{vec2f{0.0f, 0.0f}},
  size{1.0f, 1.0f},
  angle{0.0f},
  center{vec2f{0.0f, 0.0f}}
{
  trans.translate(position - center).scale(size, center).rotate(angle, center);
}

DrawObject::~DrawObject() {
  if (dr_ptr != nullptr)
    delete dr_ptr;
}

void DrawObject::setParent(DrawObject* _parent) {
  parent = _parent;
}

// void DrawObject::setAbsolutePos(vec2f pos) {
//   // do only if useful
// }

// vec2f DrawObject::getAbsolutePos() const {
//   vec2f offset{0, 0};
//   DrawObject* p = parent;
//   while (p != NULL) {
//     offset += p->trans.position;
//     p = p->parent;
//   }
//   return offset + pos;
// }

Transform DrawObject::getAbsoluteTransform() const {
  Transform t2(trans);
  DrawObject* p = parent;
  while (p != NULL) {
    t2 = p->trans * t2;
    p = p->parent;
  }
  return t2;
}

void DrawObject::draw(RenderTarget& win) const {
  win.draw(*dr_ptr, getAbsoluteTransform());
}

void DrawObject::move(float x, float y) {
  position.x += x;
  position.y += y;

  //TODO: put this in a fonction
  trans = Transform::Identity;
  trans.translate(position - center).scale(size, center).rotate(angle, center);
}

void DrawObject::move(vec2f v) {
  move(v.x, v.y);
}

void DrawObject::move(vec2i v) {
  move(v.x, v.y);
}

void DrawObject::scale(float x, float y, float origX, float origY) {
  trans.scale(x, y, origX, origY);
  size.x *= x;
  size.y *= y;
  //TODO: change pos according to origY and origX
}

void DrawObject::scale(float x, float y) {
  trans.scale(x, y);
  size.x *= x;
  size.y *= y;
}

void DrawObject::scale(vec2f v) {
  scale(v.x, v.y);
}

void DrawObject::rotate(float _angle) {
  trans.rotate(_angle, center);
  angle += _angle;
}

void DrawObject::rotate(float _angle, float cx, float cy) {
  trans.rotate(_angle, cx, cy);
  angle += _angle;
  //TODO: change pos according to origY and origX
}

void DrawObject::setPosition(float x, float y) {
  position.x = x;
  position.y = y;
  
  trans = Transform::Identity;
  trans.translate(position - center).scale(size, center).rotate(angle, center);
}