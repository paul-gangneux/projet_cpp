#ifndef VIEW_GAMEVIEWCARCASSONE_HPP
#define VIEW_GAMEVIEWCARCASSONE_HPP

#include <list>
#include "model/tile/TileCarcassonne.hpp"
#include "view/drawobject/DrawMeeple.hpp"
#include "view/gameview/GameView.hpp"

class GameViewCarcassonne : public GameView {
 private:
  typedef struct {
    DrawMeeple* meeple;
    int info[3];
  } MeepleData;

  TileCarcassonne* curModelTile;
  bool skipTurn;
  DrawText* scoreText;
  std::list<MeepleData> meepleList;
  DrawObject* lastPlacedTile;
  DrawMeeple* potentialMeeple;
  vec2i lastPlacedTilePos;
  bool lastTileHasMonastery;

  void tryToPlaceMeeple(int dir);
  int calculateMeepleDirection();
  void grabNextTile();
  std::string getAllPlayerInfo() const;

 public:
  GameViewCarcassonne(Win* win, int nbOfPlayers);
  virtual ~GameViewCarcassonne();

  virtual void changeState();
  virtual int onKeyPress(sf::Event& event);
  virtual void drawTiles();
};

#endif