#include "view/DrawObject.hpp"

using namespace std;

DrawObject::DrawObject() : parent{nullptr}, pos{0, 0} {}

DrawObject::~DrawObject() {}

void DrawObject::setParent(DrawObject* _parent) {
  parent = _parent;
}

void DrawObject::setAbsolutePos(vec2 pos) {
  // TODO (only if useful)
}

vec2 DrawObject::getAbsolutePos() const {
  vec2 offset{0, 0};
  DrawObject* p = parent;
  while (p != NULL) {
    offset += p->pos;
    p = p->parent;
  }
  return offset + pos;
}