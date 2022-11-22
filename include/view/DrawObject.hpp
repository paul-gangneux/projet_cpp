#ifndef VIEW_DRAWOBJECT_HPP
#define VIEW_DRAWOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "geometry/vectors.hpp"

class DrawObject : sf::Transformable {
private:
  DrawObject* parent;
  sf::Drawable* dr_ptr;
  sf::Transformable* tr_ptr;

public:
  // transform relative to parent, or to world if parent is null
  sf::Transform trans;

  DrawObject();

  template <typename T>
  DrawObject(T* object) :
    parent{nullptr},
    dr_ptr{(sf::Drawable*) object},
    tr_ptr{(sf::Transformable*) object},
    trans{sf::Transform::Identity}
  {}

  virtual ~DrawObject();

  void setParent(DrawObject* parent);
  sf::Transform getAbsoluteTransform() const;
  virtual void draw(sf::RenderTarget& win) const;

  // void setAbsolutePos(vec2f pos); do only if useful
  // vec2f getAbsolutePos() const;

  void move(float x, float y);
  void move(vec2i);

  void scale(float x, float y);
  void scale(vec2f);

  void rotate(float angle);

};

#endif
