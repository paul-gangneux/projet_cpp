#include "model/Board.hpp"
// #include <iostream>

Board::Board() : tileArray{RelativeVector<RelativeVector<Tile*>>()} {}

Board::~Board() {
  tileArray.forEach([](RelativeVector<Tile*> arr) {
    arr.forEach([](Tile* tile) {
      if (tile != nullptr)
        delete tile;
    });
  });
}

void Board::placeTileForced(Tile* const tile, int x, int y) {
  tileArray.expand(x);
  tileArray[x].expand(y);
  tileArray[x][y] = tile;
}

bool Board::isEmptySpace(int x, int y) {
  return (outOfBounds(x, y) || tileArray[x][y] == nullptr);
}

bool Board::isAdjacent(int x, int y) {
  return (
      (!isEmptySpace(x - 1, y)) || (!isEmptySpace(x + 1, y)) ||
      (!isEmptySpace(x, y - 1)) || (!isEmptySpace(x, y + 1)));
}

bool Board::outOfBounds(int x, int y) {
  return (tileArray.outOfBounds(x) || tileArray[x].outOfBounds(y));
}

bool Board::placeTile(Tile* const tile, int x, int y) {
  if (isEmptySpace(x, y) && isAdjacent(x, y) &&
      (outOfBounds(x - 1, y) || (tileArray[x - 1][y] == nullptr) ||
       tileArray[x - 1][y]->matchX(tile)) &&
      (outOfBounds(x + 1, y) || (tileArray[x + 1][y] == nullptr) ||
       tile->matchX(tileArray[x + 1][y])) &&
      (outOfBounds(x, y - 1) || (tileArray[x][y - 1] == nullptr) ||
       tileArray[x][y - 1]->matchY(tile)) &&
      (outOfBounds(x, y + 1) || (tileArray[x][y + 1] == nullptr) ||
       tile->matchY(tileArray[x][y + 1]))) {
    placeTileForced(tile, x, y);
    return true;
  }
  return false;
}

Tile* Board::get(int x, int y) {
  if (outOfBounds(x, y))
    return nullptr;
  return tileArray[x][y];
}
