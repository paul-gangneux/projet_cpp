#ifndef MODEL_GAME_TREX_HPP
#define MODEL_GAME_TREX_HPP

#include <queue>

#include "Game.hpp"
#include "geometry/vectors.hpp"
#include "model/tile/TileTrax.hpp"

class GameTrax : public Game {
 private:
  // std::vector<GameTrax*> bag;
  std::queue<int*> placedTilesQueue;
  int nbOfTiles;
  int minX, maxX, minY, maxY;

  void playIfForced(int x, int y);
  char getColorIfExists(int x, int y, int colorPos);
  void checkForEndGame(int x, int y);
  bool checkPath(vec2i pos, vec2i ori, bool xtrm[4], char col, int dir);
  bool placeTileAux(Tile* const tile, int x, int y);

 public:
  GameTrax();
  ~GameTrax();

  bool canAddNewPlayer();
  virtual bool placeTile(Tile* const tile, int x, int y);

  // fills the array with info about a tile in the recently placed queue.
  // returns false if queue is empty
  // infos are: type, x pos, y pos, rotation
  bool getTileInfoInPlaceQueue(int infos[4]);
};

#endif