#ifndef MODEL_GAME_DOMINO_HPP
#define MODEL_GAME_DOMINO_HPP

#include "model/game/Game.hpp"
#include "model/tile/TileDomino.hpp"

class GameDomino : public Game {
 private:
  std::vector<TileDomino*> bag;

 public:
  GameDomino();
  ~GameDomino();

  bool canAddNewPlayer();
  Tile* grabTile();  // not 100% sure this works since i return a Tile* not
                     // TileDomino*. don't forget to cast
  bool placeTile(Tile* const, int x, int y);
  void discardTile(Tile*);  // maybe need to add const so that incoming tiles
                            // will be accepted
};

#endif