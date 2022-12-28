#ifndef VIEW_GAMEVIEWCARCASSONE_HPP
#define VIEW_GAMEVIEWCARCASSONE_HPP

// #include "model/tile/TileCarcassone.hpp"
#include "view/gameview/GameView.hpp"

class GameViewCarcassone : public GameView {
 private:
  // TileCarcassone* curModelTile;
  bool skipTurn;
  DrawText* scoreText;

 public:
  GameViewCarcassone(Win* win);
  virtual ~GameViewCarcassone();

  virtual void changeState();
  virtual int onKeyPress(sf::Event& event);
};

#endif