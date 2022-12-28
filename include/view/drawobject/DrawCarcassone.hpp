#ifndef VIEW_DRAWCARCASSONE_HPP
#define VIEW_DRAWCARCASSONE_HPP

//#include "model/tile/TileCarcassone.hpp"
#include "view/drawobject/DrawObject.hpp"
//#include "view/drawobject/DrawText.hpp"

class DrawCarcassone : public DrawObject {
 public:
  static sf::Texture textures[24];
  static sf::Sprite* createCarcassoneSprite(int type);
  // todo: meeples

 public:
  DrawCarcassone(int type);
  virtual ~DrawCarcassone();

  static void initTextures();

  virtual void rotate(float angle);
  virtual void setRotation(float angle);
  virtual void draw(sf::RenderTarget* win) const;
};

#endif
