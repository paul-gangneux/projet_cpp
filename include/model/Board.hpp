#ifndef MODEL_BOARD_HPP
#define MODEL_BOARD_HPP

#include <vector>
#include "RelativeVector.hpp"
#include "tile/Tile.hpp"

class Board {
 private:
  RelativeVector<RelativeVector<Tile*>> tileArray;

  // checks if there is already a Tile at the given coordinates
  bool isEmptySpace(int x, int y);

  // checks if any of the 4 adjacent squares are occupied by a Tile
  bool isAdjacent(int x, int y);

 public:
  Board();
  virtual ~Board();

  // used to place the first Tile of a game
  void placeTileForced(int x, int y, Tile* const tile);
  bool outOfBounds(int x, int y);
  bool placeTile(int x, int y, Tile* const tile);
  // returns null if coords are out of bounds
  Tile* get(int x, int y);
};

#endif