#ifndef VIEW_GAMEVIEWCARCASSONE_HPP
#define VIEW_GAMEVIEWCARCASSONE_HPP

#include <list>
#include "model/tile/TileCarcassonne.hpp"
#include "view/drawobject/DrawMeeple.hpp"
#include "view/gameview/GameView.hpp"

class GameViewCarcassonne : public GameView {
 private:
  TileCarcassonne* curModelTile;
  bool skipTurn;
  DrawText* scoreText;
  std::list<DrawMeeple*> meepleList;
  DrawObject* lastPlacedTile;
  DrawMeeple* potentialMeeple;

  void tryToPlaceMeeple(int dir);
  int calculateMeepleDirection();

 public:
  GameViewCarcassonne(Win* win);
  virtual ~GameViewCarcassonne();

  virtual void changeState();
  virtual int onKeyPress(sf::Event& event);
  virtual void drawTiles();
};

#endif