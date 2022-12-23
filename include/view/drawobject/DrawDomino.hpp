#ifndef VIEW_DRAWDOMINO_HPP
#define VIEW_DRAWDOMINO_HPP

#include "model/tile/TileDomino.hpp"
#include "view/drawobject/DrawObject.hpp"
#include "view/drawobject/DrawText.hpp"

class DrawDomino : public DrawObject {
 private:
  static sf::Texture texture;
  static sf::Texture initTexture();
  static sf::Sprite* createDominoSprite();
  /*
  ++ T0 T1 T2 ++
  T11 ------- T3
  T10 ------- T4
  T9  ------- T5
  ++ T8 T7 T6 ++
  */
  DrawText* numbers[12];

 public:
  DrawDomino(TileDomino* domino);
  ~DrawDomino();

  virtual void rotate(float angle);
  virtual void setRotation(float angle);
  virtual void draw(sf::RenderTarget* win) const;
};

#endif
