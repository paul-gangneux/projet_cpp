#include "model/tile/TileTrax.hpp"
#include <iostream>
#include <ctime>

TileTrax::TileTrax() {
  //todo
}

TileTrax::~TileTrax() {

}

void TileTrax::rotateClockwise() {
  //todo
}

void TileTrax::rotateCounterClockwise() {
  //todo
}

/* [WARNING !]
 * this function must be called in the following way : tile1.matchX(tile2)
 * with tile1 being the tile IMMEDIATELY ON THE LEFT of tile2.
 * in other words, the X coordinate of tile1 must be the X coordinate of tile2 minus 1.
*/
bool TileTrax::matchX(Tile* right) {
  //todo
  return true;
}

/* [WARNING !]
 * this function must be called in the following way : tile1.matchY(tile2)
 * with tile1 being the tile IMMEDIATELY UPWARDS of tile2.
 * in other words, the Y coordinate of tile1 must be the Y coordinate of tile2 minus 1.
*/
bool TileTrax::matchY(Tile* down) {
  //todo
  return true;
}