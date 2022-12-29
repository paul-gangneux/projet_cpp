#ifndef VIEW_GAMEVIEWCARCASSONE_HPP
#define VIEW_GAMEVIEWCARCASSONE_HPP

#include "model/tile/TileCarcassonne.hpp"
#include "view/gameview/GameView.hpp"

class GameViewCarcassonne : public GameView {
 private:
  TileCarcassonne* curModelTile;
  bool skipTurn;
  DrawText* scoreText;

  void tryToPlaceMeeple(int dir);

 public:
  GameViewCarcassonne(Win* win);
  virtual ~GameViewCarcassonne();

  virtual void changeState();
  virtual int onKeyPress(sf::Event& event);
};

#endif