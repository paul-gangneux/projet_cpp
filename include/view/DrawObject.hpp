#ifndef VIEW_DRAWOBJECT_HPP
#define VIEW_DRAWOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "geometry/vectors.hpp"

class DrawObject : public sf::Transformable {
private:
  DrawObject* parent;
  sf::Drawable* dr_ptr;
  sf::Transformable* tr_ptr;

protected:
  // transform relative to parent, or to world if parent is null
  sf::Transform trans;
  vec2f position;
  vec2f size;
  float angle;
  vec2f center;

public:
  DrawObject();

  template <typename T>
  DrawObject(T* object) :
    parent{nullptr},
    dr_ptr{(sf::Drawable*) object},
    tr_ptr{(sf::Transformable*) object},
    trans{sf::Transform::Identity},
    position{vec2f{0.0f, 0.0f}},
    size{1.0f, 1.0f},
    angle{0.0f},
    center{vec2f{0.0f, 0.0f}}
  {
    trans.translate(position - center).scale(size, center).rotate(angle, center);
  }

  virtual ~DrawObject();

  void setParent(DrawObject* parent);
  sf::Transform getAbsoluteTransform() const;
  virtual void draw(sf::RenderTarget& win) const;

  // void setAbsolutePos(vec2f pos); do only if useful
  // vec2f getAbsolutePos() const;

  vec2f getSize() const {
    return size;
  }

  void move(float x, float y);
  void move(vec2i);
  void move(vec2f);

  void setPosition(float x, float y);
  void setPosition(vec2f);

  void scale(float x, float y, float origX, float origY);
  void scale(float x, float y);
  void scale(vec2f);

  void rotate(float angle);
  void rotate(float angle, float centerX, float centerY);
};

#endif
