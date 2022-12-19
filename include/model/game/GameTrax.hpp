#ifndef MODEL_GAME_TREX_HPP
#define MODEL_GAME_TREX_HPP

#include "Game.hpp"
#include "model/tile/TileTrax.hpp"
#include <queue>

class GameTrax : public Game {
private:
  // std::vector<GameTrax*> bag;
  std::queue<int*> placedTilesQueue;
  bool gameOver();
  void playIfForced(int x, int y);
  char getColorIfExists(int x, int y, int colorPos);

public:
  GameTrax();
  ~GameTrax();

  bool canAddNewPlayer();
  virtual bool placeTile(Tile* const tile, int x, int y);
  // fills the array with info abuot a tile in the recently placed queue.
  // returns false if queue is empty
  // infos are: type, x pos, y pos, rotation
  bool getTileInfoInPlaceQueue(int infos[4]);
};

#endif