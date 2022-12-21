#ifndef MODEL_BOARD_HPP
#define MODEL_BOARD_HPP

#include "RelativeVector.hpp"
#include <vector>
#include "tile/Tile.hpp"

class Board {
private:
  RelativeVector<RelativeVector<Tile*>> tileArray;

  bool isEmptySpace(int x, int y); //checks if there is already a Tile at the given coordinates
  bool isAdjacent(int x, int y); //checks if any of the 4 adjacent squares are occupied by a Tile
public:
  Board();
  virtual ~Board();

  void placeTileForced(Tile* const tile, int x, int y); //used to place the first Tile of a game
  bool outOfBounds(int x, int y);
  bool placeTile(Tile* const tile, int x, int y);
  // returns null if coords are out of bounds
  Tile* get(int x, int y);
};

#endif