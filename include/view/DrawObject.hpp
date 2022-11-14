#ifndef VIEW_DRAWOBJECT_HPP
#define VIEW_DRAWOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "geometry/vectors.hpp"

class DrawObject {
private:
  DrawObject* parent;

public:
  // position relative to parent, or to world if parent is null
  vec2 pos;

  DrawObject();
  virtual ~DrawObject();

  void setParent(DrawObject* parent);
  void setAbsolutePos(vec2 pos);
  vec2 getAbsolutePos() const;
  // virtual void draw(/* args needed here */) const; TODO
};

#endif
