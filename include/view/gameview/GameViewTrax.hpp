#ifndef VIEW_GAMEVIEWTraxTRAX_HPP
#define VIEW_GAMEVIEWTraxTRAX_HPP

#include <iostream>
#include <list>

#include "geometry/vectors.hpp"
#include "view/Win.hpp"
#include "view/drawobject/DrawDomino.hpp"
#include "view/drawobject/DrawObject.hpp"
#include "view/drawobject/DrawText.hpp"
#include "view/gameview/GameView.hpp"

class GameViewTrax : public GameView {
 private:
  int tileType;

 public:
  GameViewTrax(Win* win);
  virtual ~GameViewTrax();

  virtual void changeState();
  virtual void onKeyPress(sf::Event& event);
};

#endif