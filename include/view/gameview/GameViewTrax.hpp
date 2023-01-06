#ifndef VIEW_GAMEVIEWTRAX_HPP
#define VIEW_GAMEVIEWTRAX_HPP

#include <iostream>
#include <list>
#include "geometry/vectors.hpp"
#include "view/Win.hpp"
#include "view/gameview/GameView.hpp"

class GameViewTrax : public GameView {
 private:
  int tileType;

 public:
  GameViewTrax(Win* win);
  virtual ~GameViewTrax();

  virtual void changeState();
  virtual int onKeyPress(sf::Event& event);
};

#endif