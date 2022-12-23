#ifndef VIEW_GAMEVIEWDOMINO_HPP
#define VIEW_GAMEVIEWDOMINO_HPP

#include "model/tile/TileDomino.hpp"
#include "view/gameview/GameView.hpp"

class GameViewDomino : public GameView {
 private:
  TileDomino* curModelTile;

 public:
  GameViewDomino(Win* win);
  virtual ~GameViewDomino();

  virtual void changeState();
  virtual int onKeyPress(sf::Event& event);
};

#endif