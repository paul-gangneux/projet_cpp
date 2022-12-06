#ifndef VIEW_DRAWTREX_HPP
#define VIEW_DRAWTREX_HPP

#include "view/drawobject/DrawObject.hpp"

class DrawTrax : public DrawObject {
private:
  static sf::Texture texture1;
  static sf::Texture texture2;
  sf::Sprite* createSprite(int type, bool transparent = false);
public:
  DrawTrax(int type, bool transparent = false);

  ~DrawTrax();

  // virtual void rotate(float angle);
  // virtual void draw(sf::RenderTarget& win) const;
};

#endif
