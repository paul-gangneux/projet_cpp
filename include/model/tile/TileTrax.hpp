#ifndef MODEL_TILE_TREX_HPP
#define MODEL_TILE_TREX_HPP

#include "Tile.hpp"

class TileTrax : public Tile {
 private:
  // 0 for straight, 1 for curved
  int type;

  // 0 to 3, corresponds to number of clockwise rotations
  int rotation;

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

  int getType() const;
  int getRotation() const;
  char getColor(int i) const;
};

#endif