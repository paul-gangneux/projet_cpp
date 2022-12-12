#ifndef MODEL_GAME_TREX_HPP
#define MODEL_GAME_TREX_HPP

#include "Game.hpp"
#include "model/tile/TileTrax.hpp"

class GameTrax : public Game {
private:
  // std::vector<GameTrax*> bag;
  bool gameOver();
public:
  GameTrax();
  ~GameTrax();

  bool canAddNewPlayer();
};

#endif