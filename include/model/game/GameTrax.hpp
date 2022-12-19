#ifndef MODEL_GAME_TREX_HPP
#define MODEL_GAME_TREX_HPP

#include <queue>
#include "Game.hpp"
#include "model/tile/TileTrax.hpp"

class GameTrax : public Game {
 private:
  // std::vector<GameTrax*> bag;
  std::queue<int*> placedTilesQueue;
  bool gameIsOver;
  int nbOfTiles;

  void playIfForced(int x, int y);
  char getColorIfExists(int x, int y, int colorPos);
  void checkForEndGame(int x, int y);
  bool checkPathForLoop(int origX, int origY, char col, int x, int y, int dir);

 public:
  GameTrax();
  ~GameTrax();

  bool canAddNewPlayer();
  virtual bool placeTile(Tile* const tile, int x, int y);

  // fills the array with info about a tile in the recently placed queue.
  // returns false if queue is empty
  // infos are: type, x pos, y pos, rotation
  bool getTileInfoInPlaceQueue(int infos[4]);

  virtual bool isOver();
};

#endif