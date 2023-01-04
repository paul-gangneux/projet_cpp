#ifndef VIEW_GAMEVIEWDOMINO_HPP
#define VIEW_GAMEVIEWDOMINO_HPP

#include "model/tile/TileDomino.hpp"
#include "view/gameview/GameView.hpp"

class GameViewDomino : public GameView {
 private:
  TileDomino* curModelTile;
  bool discardTile;
  DrawText* scoreText;

 public:
  GameViewDomino(Win* win, int nbOfPlayers);
  virtual ~GameViewDomino();

  virtual void changeState();
  virtual int onKeyPress(sf::Event& event);
};

#endif