#ifndef MODEL_GAME_DOMINO_HPP
#define MODEL_GAME_DOMINO_HPP

#include "model/game/Game.hpp"
#include "model/tile/TileDomino.hpp"

class GameDomino : public Game {
 private:
  /// contains all the (randomly generated) tiles that will be played
  /// during the game. once it is empty, the game is over.
  std::vector<TileDomino*> bag;

 public:
  GameDomino();
  virtual ~GameDomino();

  /// always returns true, since we can have an
  /// infinite number of players on a domino game.
  virtual bool canAddNewPlayer();

  /// returns a Tile* from the bag.
  /// however, it points to a TileDomino, so we will use casting later.
  Tile* grabTile();
  // i named it "grab", as using "get" or "draw" might be misleading

  /// tries to place a tile at coordinates x y,
  /// returns false if the placement was invalid (= tile wasn't placed).
  ///
  /// if the tile was placed correctly : returns true,
  /// proceeds to the next turn,
  /// checks if the bag is empty - if it is, changes gameIsOver to true
  virtual bool placeTile(Tile* const, int x, int y);

  /// deletes the tile and proceed to the next turn.
  /// checks if the bag is empty - if it is, changes gameIsOver to true
  void discardTile(Tile* const);
};

#endif