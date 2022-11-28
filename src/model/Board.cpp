#include "model/Board.hpp"

void Board::placeTileForced(int x, int y, Tile* const tile) {
  tileArray[x][y] = tile;
}

bool Board::isEmptySpace(int x, int y) {
  return (tileArray[x][y] != nullptr);
}

bool Board::isAdjacent(int x, int y) {
  return ((!isEmptySpace(x - 1, y)) || (!isEmptySpace(x + 1, y))
    || (!isEmptySpace(x, y - 1)) || (!isEmptySpace(x, y + 1)));
}

bool Board::outOfBounds(int x, int y) {
  return (
    tileArray.outOfBounds(x) ||
    tileArray[x].outOfBounds(y)
    );
}

bool Board::placeTile(int x, int y, Tile* const tile) {
  if (
    isEmptySpace(x, y) &&
    isAdjacent(x, y) &&
    (outOfBounds(x - 1, y) || (tileArray[x - 1][y] == nullptr) || (*tileArray[x - 1][y]).matchX(tile)) &&
    (outOfBounds(x + 1, y) || (tileArray[x + 1][y] == nullptr) || (*tile).matchX(tileArray[x + 1][y])) &&
    (outOfBounds(x, y - 1) || (tileArray[x][y - 1] == nullptr) || (*tileArray[x][y - 1]).matchY(tile)) &&
    (outOfBounds(x, y + 1) || (tileArray[x][y + 1] == nullptr) || (*tile).matchY(tileArray[x][y + 1]))
    ) {
    placeTileForced(x, y, tile);
    return true;
  }
  return false;
}
