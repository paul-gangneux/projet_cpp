#ifndef MODEL_TILE_TREX_HPP
#define MODEL_TILE_TREX_HPP

#include "Tile.hpp"

class TileTrax : public Tile {
private:
  // w for white, b for black
  // positions for colors are:
  // --0--
  // 3---1
  // --2--
  char colors[4];
public:
  TileTrax(int type);
  TileTrax(int type, int rotation);
  virtual ~TileTrax();

  void rotateClockwise();
  void rotateCounterClockwise();

  bool matchX(const Tile* right) const;
  bool matchY(const Tile* down) const;
};

#endif