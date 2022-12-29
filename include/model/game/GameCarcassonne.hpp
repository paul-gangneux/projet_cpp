#ifndef MODEL_GAME_CARCASSONE_HPP
#define MODEL_GAME_CARCASSONE_HPP

#include "model/game/Game.hpp"
#include "model/tile/TileCarcassonne.hpp"

class GameCarcassonne : public Game {
 private:
  /// contains all the tiles that will be played
  /// during the game. once it is empty, the game is over.
  std::vector<TileCarcassonne*> bag;

 public:
  GameCarcassonne();
  virtual ~GameCarcassonne();

  virtual bool canAddNewPlayer();

  /// returns a Tile* from the bag.
  /// however, it points to a TileCarcassonne, so we will use casting later.
  Tile* grabTile();

  /// tries to place a tile at coordinates x y,
  /// returns false if the placement was invalid (= tile wasn't placed).
  ///
  /// if the tile was placed correctly : returns true,
  /// checks if the bag is empty - if it is, changes gameIsOver to true
  virtual bool placeTile(Tile* const, int x, int y);
};

#endif