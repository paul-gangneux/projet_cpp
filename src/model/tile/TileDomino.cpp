#include "model/tile/TileDomino.hpp"
#include <iostream>

TileDomino::TileDomino() : numbers{new int[12]} {
  for (int i = 0; i < 12; i++) {
    numbers[i] = rand() % 5;
  }
}

TileDomino::~TileDomino() {
  delete[] numbers;
}

int const* TileDomino::getNumbers() const {
  return numbers;
}

// If you are confused on how the following functions work, please check
// TileDomino.hpp

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

bool TileDomino::matchX(const Tile* right) const {
  const TileDomino* local = dynamic_cast<const TileDomino*>(right);
  if (local == nullptr)
    return false;
  return (
      (this->numbers[3] == local->numbers[11]) &&
      (this->numbers[4] == local->numbers[10]) &&
      (this->numbers[5] == local->numbers[9]));
}

bool TileDomino::matchY(const Tile* down) const {
  const TileDomino* local = dynamic_cast<const TileDomino*>(down);
  if (local == nullptr)
    return false;
  return (
      (this->numbers[8] == local->numbers[0]) &&
      (this->numbers[7] == local->numbers[1]) &&
      (this->numbers[6] == local->numbers[2]));
}