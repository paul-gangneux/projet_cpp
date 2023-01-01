#ifndef VIEW_DRAWCARCASSONE_HPP
#define VIEW_DRAWCARCASSONE_HPP

#include "view/drawobject/DrawObject.hpp"

class DrawCarcassonne : public DrawObject {
 public:
  static sf::Texture textures[24];
  static sf::Sprite* createCarcassonneSprite(int type);

 public:
  DrawCarcassonne(int type);
  virtual ~DrawCarcassonne();

  static void initTextures();

  virtual void rotate(float angle);
  virtual void setRotation(float angle);
  virtual void draw(sf::RenderTarget* win) const;
};

#endif
