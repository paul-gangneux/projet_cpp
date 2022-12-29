#ifndef VIEW_DRAWMEEPLE_HPP
#define VIEW_DRAWMEEPLE_HPP

#include "view/drawobject/DrawObject.hpp"

class DrawMeeple : public DrawObject {
 public:
  static sf::Texture textures[4];
  static sf::Sprite* createMeepleSprite(int player);
  int dir;

 public:
  DrawMeeple(int player);
  virtual ~DrawMeeple();

  static void initTextures();
};

#endif
