#ifndef MODEL_GAME_TREX_HPP
#define MODEL_GAME_TREX_HPP

#include "Game.hpp"
#include "model/tile/TileTrex.hpp"

class GameTrex : public Game {
private:
  // std::vector<GameTrex*> bag;
  void gameOver();
public:
  GameTrex();
  ~GameTrex();

  bool canAddNewPlayer();
  Tile* grabTile();
};

#endif