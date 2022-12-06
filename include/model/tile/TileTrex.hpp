#ifndef MODEL_TILE_TREX_HPP
#define MODEL_TILE_TREX_HPP

#include "Tile.hpp"

class TileTrex : public Tile {
private:
  // 0 for white, 1 for black
  char colors[4];
public:
  TileTrex();
  virtual ~TileTrex();

  void rotateClockwise();
  void rotateCounterClockwise();

  bool matchX(Tile* right);
  bool matchY(Tile* down);
};

#endif