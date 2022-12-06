#include "model/tile/TileDomino.hpp"
#include <iostream>
#include <ctime>

TileDomino::TileDomino() :
  numbers{new int[12]}
{
  std::srand(std::time(nullptr));
  for (int i = 0; i < 12; i++) {
    numbers[i] = rand() % 5;
  }
}

TileDomino::~TileDomino() {
  delete numbers;
}

// If you are confused on how the following functions work, please check TileDomino.hpp

void TileDomino::rotateClockwise() {
  int temp[3] = {numbers[9], numbers[10], numbers[11]};
  for (int i = 11; i > 2; i--) {
    numbers[i] = numbers[(i + 9) % 12];
  }
  for (int i = 0; i < 3; i++) {
    numbers[i] = temp[i];
  }
}

void TileDomino::rotateCounterClockwise() {
  int temp[3] = {numbers[0], numbers[1], numbers[2]};
  for (int i = 0; i < 9; i++) {
    numbers[i] = numbers[i + 3];
  }
  for (int i = 9; i < 12; i++) {
    numbers[i] = temp[i - 9];
  }
}

/* [WARNING !]
 * this function must be called in the following way : tile1.matchX(tile2)
 * with tile1 being the tile IMMEDIATELY ON THE LEFT of tile2.
 * in other words, the X coordinate of tile1 must be the X coordinate of tile2 minus 1.
*/
bool TileDomino::matchX(Tile* right) {
  TileDomino* local = dynamic_cast<TileDomino*>(right);
  if (local == nullptr) return false;
  return (
    (this->numbers[3] == local->numbers[11]) &&
    (this->numbers[4] == local->numbers[10]) &&
    (this->numbers[5] == local->numbers[9])
    );
}

/* [WARNING !]
 * this function must be called in the following way : tile1.matchY(tile2)
 * with tile1 being the tile IMMEDIATELY UPWARDS of tile2.
 * in other words, the Y coordinate of tile1 must be the Y coordinate of tile2 minus 1.
*/
bool TileDomino::matchY(Tile* down) {
  TileDomino* local = dynamic_cast<TileDomino*>(down);
  if (local == nullptr) return false;
  return (
    (this->numbers[8] == local->numbers[0]) &&
    (this->numbers[7] == local->numbers[1]) &&
    (this->numbers[6] == local->numbers[2])
    );
}