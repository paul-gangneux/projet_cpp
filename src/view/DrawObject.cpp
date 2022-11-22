#include "view/DrawObject.hpp"

using namespace std;

DrawObject::DrawObject() :
  parent{nullptr},
  dr_ptr{nullptr},
  tr_ptr{nullptr},
  trans{sf::Transform::Identity}
{}

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

sf::Transform DrawObject::getAbsoluteTransform() const {
  sf::Transform t2(trans);
  DrawObject* p = parent;
  while (p != NULL) {
    t2 = p->trans * t2;
    p = p->parent;
  }
  return t2;
}

// a bit weird and complex for nothing, would be worth re-thinking
void DrawObject::draw(sf::RenderTarget& win) const {
  win.draw(*dr_ptr, getAbsoluteTransform());
}

void DrawObject::move(float x, float y) {
  trans.translate(x, y);
}

void DrawObject::move(vec2i v) {
  move(v.x, v.y);
}

void DrawObject::scale(float x, float y) {
  trans.scale(x, y);
}

void DrawObject::scale(vec2f v) {
  scale(v.x, v.y);
}

void DrawObject::rotate(float angle) {
  trans.rotate(angle);
}