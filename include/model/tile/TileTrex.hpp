#ifndef MODEL_TILE_TREX_HPP
#define MODEL_TILE_TREX_HPP

#include "Tile.hpp"

class TileTrax : public Tile {
private:
  // 0 for white, 1 for black
  char colors[4];
public:
  TileTrax();
  virtual ~TileTrax();

  void rotateClockwise();
  void rotateCounterClockwise();

  bool matchX(Tile* right);
  bool matchY(Tile* down);
};

#endif