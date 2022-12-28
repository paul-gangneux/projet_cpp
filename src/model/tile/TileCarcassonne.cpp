#include "model/tile/TileCarcassonne.hpp"

#include <iostream>

TileCarcassonne::TileCarcassonne() {}

TileCarcassonne::~TileCarcassonne() {}

void TileCarcassonne::rotateClockwise() {
  int temp[3] = {dir[9], dir[10], dir[11]};
  for (int i = 11; i > 2; i--) {
    dir[i] = dir[(i + 9) % 12];
  }
  for (int i = 0; i < 3; i++) {
    dir[i] = temp[i];
  }

  for (edge e : edges) {
    e.rotateClockwise();
  }

  meepleLocation = (meepleLocation + 3) % 12;
}

void TileCarcassonne::rotateCounterClockwise() {
  int temp[3] = {dir[0], dir[1], dir[2]};
  for (int i = 0; i < 9; i++) {
    dir[i] = dir[i + 3];
  }
  for (int i = 9; i < 12; i++) {
    dir[i] = temp[i - 9];
  }

  for (edge e : edges) {
    e.rotateCounterClockwise();
  }

  meepleLocation = (meepleLocation + 9) % 12;
}

char TileCarcassonne::getDir(int a) const {
  if (a < 0)
    return dir[0];
  if (a > 11)
    return dir[11];
  return dir[a];
}

bool TileCarcassonne::matchX(const Tile* right) const {
  const TileCarcassonne* local = dynamic_cast<const TileCarcassonne*>(right);
  if (local == nullptr)
    return false;

  return (tolower(dir[3]) == tolower(local->getDir(9)));
}

bool TileCarcassonne::matchY(const Tile* down) const {
  const TileCarcassonne* local = dynamic_cast<const TileCarcassonne*>(down);
  if (local == nullptr)
    return false;

  return (tolower(dir[6]) == tolower(local->getDir(0)));
}