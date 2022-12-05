#ifndef VIEW_DRAWTREX_HPP
#define VIEW_DRAWTREX_HPP

#include "view/DrawObject.hpp"

class DrawTrex : public DrawObject {
private:
  static sf::Texture texture1;
  static sf::Texture texture2;
  sf::Sprite* createSprite(int type);
public:
  DrawTrex(int type);
  ~DrawTrex();

  // virtual void rotate(float angle);
  // virtual void draw(sf::RenderTarget& win) const;
};

#endif
