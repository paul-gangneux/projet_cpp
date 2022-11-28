#ifndef MODEL_GAME_DOMINO_HPP
#define MODEL_GAME_DOMINO_HPP

#include "Game.hpp"
#include "TileDomino.hpp"

class GameDomino : public Game {
private:
  std::vector<TileDomino*> bag;
  void gameOver();
public:
  Tile* grabTile(); // not 100% sure this works since i return a Tile* not TileDomino*. don't forget to cast
};

#endif