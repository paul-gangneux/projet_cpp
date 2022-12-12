#include "model/tile/TileTrax.hpp"
#include <iostream>
#include <ctime>

TileTrax::TileTrax(int type) {
  if (type == 0) {
    colors[0] = 'b';
    colors[1] = 'w';
    colors[2] = 'b';
    colors[3] = 'w';
  }
  else {
    colors[0] = 'w';
    colors[1] = 'w';
    colors[2] = 'b';
    colors[3] = 'b';
  }
}

TileTrax::TileTrax(int type, int rot) : TileTrax(type) {
  if (rot <= 3 && rot >= 0) {
    for (int i = 0; i < rot; i++) {
      rotateClockwise();
    }
  }
}

TileTrax::~TileTrax() {
  // nothing to do
}

void TileTrax::rotateClockwise() {
  char tmp = colors[3];
  colors[3] = colors[2];
  colors[2] = colors[1];
  colors[1] = colors[0];
  colors[0] = tmp;
}

void TileTrax::rotateCounterClockwise() {
  char tmp = colors[0];
  colors[0] = colors[1];
  colors[1] = colors[2];
  colors[2] = colors[3];
  colors[3] = tmp;
}

/* [WARNING !]
 * this function must be called in the following way : tile1.matchX(tile2)
 * with tile1 being the tile IMMEDIATELY ON THE LEFT of tile2.
 * in other words, the X coordinate of tile1 must be the X coordinate of tile2 minus 1.
*/
bool TileTrax::matchX(const Tile* right) const {
  const TileTrax* _right = dynamic_cast<const TileTrax*>(right);
  return (colors[1] == _right->colors[3]);
}

/* [WARNING !]
 * this function must be called in the following way : tile1.matchY(tile2)
 * with tile1 being the tile IMMEDIATELY UPWARDS of tile2.
 * in other words, the Y coordinate of tile1 must be the Y coordinate of tile2 minus 1.
*/
bool TileTrax::matchY(const Tile* down) const {
  const TileTrax* _down = dynamic_cast<const TileTrax*>(down);
  return (colors[2] == _down->colors[0]);
}