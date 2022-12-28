#include "model/tile/TileCarcassonne.hpp"

#include <iostream>
#include <string>

#define DIR(a)       \
  {                  \
    dir[0] = (a)[0]; \
    dir[1] = (a)[1]; \
    dir[2] = (a)[2]; \
    dir[3] = (a)[3]; \
  }

#define EDGE(a, b) edges.push_back(edge(a, b));

TileCarcassonne::TileCarcassonne(uint8_t _type) :
    type{_type},
    edges{std::vector<edge>()},
    monastery{false},
    meeplePlayer{-1},
    meepleLocation{-1} {
  switch (type) {
    case 1:
      DIR("ggrr")
      EDGE(6, 9)
      EDGE(10, 0)
      EDGE(0, 3)
      EDGE(3, 5)
      EDGE(7, 8)
      break;
    case 2:
      DIR("trrg")
      EDGE(3, 6)
      EDGE(4, 5)
      EDGE(7, 9)
      EDGE(9, 2)
      break;
    case 3:
      DIR("Trrt")
      EDGE(0, 9)
      EDGE(3, 6)
      EDGE(2, 7)
      EDGE(4, 5)
  }
}

TileCarcassonne::~TileCarcassonne() {
  // nothing to do
}

void TileCarcassonne::rotateClockwise() {
  int temp = dir[3];
  dir[3] = dir[2];
  dir[2] = dir[1];
  dir[1] = dir[0];
  dir[0] = temp;

  for (edge e : edges) {
    e.rotateClockwise();
  }

  meepleLocation = (meepleLocation + 3) % 12;
}

void TileCarcassonne::rotateCounterClockwise() {
  int temp = dir[0];
  dir[0] = dir[1];
  dir[1] = dir[2];
  dir[2] = dir[3];
  dir[3] = temp;

  for (edge e : edges) {
    e.rotateCounterClockwise();
  }

  meepleLocation = (meepleLocation + 9) % 12;
}

char TileCarcassonne::getDir(int a) const {
  if (a < 0)
    return dir[0];
  // technically we should only call this function with a value between 0 and 3,
  // but just in case:
  return dir[a % 4];
}

bool TileCarcassonne::matchX(const Tile* right) const {
  const TileCarcassonne* local = dynamic_cast<const TileCarcassonne*>(right);
  if (local == nullptr)
    return false;

  return (tolower(dir[1]) == tolower(local->getDir(3)));
}

bool TileCarcassonne::matchY(const Tile* down) const {
  const TileCarcassonne* local = dynamic_cast<const TileCarcassonne*>(down);
  if (local == nullptr)
    return false;

  return (tolower(dir[2]) == tolower(local->getDir(0)));
}