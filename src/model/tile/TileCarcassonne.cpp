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
      break;
    case 4:
      DIR("ttrt")
      EDGE(0, 3)
      EDGE(0, 9)
      // EDGE(3, 9)  // redundant ?
      break;
    case 5:
      DIR("Ttgt")
      EDGE(0, 3)
      EDGE(0, 9)
      // EDGE(3, 9)  // redundant ?
      break;
    case 6:
      DIR("trrt")
      EDGE(0, 9)
      EDGE(3, 6)
      EDGE(2, 7)
      EDGE(4, 5)
      break;
    case 7:
      DIR("trrr")
      // I'm not sure if the roads
      // are connected here
      break;
    case 8:
      DIR("rgrg")
      EDGE(0, 6);
      EDGE(1, 3);
      EDGE(3, 5);
      // EDGE(1, 5);  // redundant ?
      EDGE(11, 9);
      EDGE(9, 7);
      // EDGE(11, 7);  // redundant ?
      break;
    case 9:
      DIR("grrr")  // >:3
      // I'm not sure if the roads
      // are connected here
      EDGE(0, 2);
      EDGE(0, 10);
      // EDGE(10, 2);  // redundant ?
      break;
    case 10:
      DIR("tggg")
      // TODO: edges
      break;
    case 11:
      DIR("ttgg")
      // TODO: edges
      break;
    case 12:
      DIR("ttgt")
      // TODO: edges
      break;
    case 13:
      DIR("gggg")
      monastery = true;
      // TODO: edges
      break;
    case 14:
      DIR("ggrg")
      monastery = true;
      // TODO: edges
      break;
    case 15:
      DIR("tggt")
      // TODO: edges
      break;
    case 16:
      DIR("gTgt")
      // TODO: edges
      break;
    case 17:
      DIR("trgr")
      // TODO: edges
      break;
    case 18:
      DIR("tgrr")
      // TODO: edges
      break;
    case 19:
      DIR("gtgt")
      // TODO: edges
      break;
    case 20:
      DIR("Ttrt")
      // TODO: edges
      break;
    case 21:
      DIR("Tttt")
      // TODO: edges
      break;
    case 22:
      DIR("rrrr")
      // TODO: edges
      break;
    case 23:
      DIR("Tggt")
      // TODO: edges
      break;
    case 24:
      DIR("gtgt")
      // TODO: edges
      break;
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

int TileCarcassonne::getType() const {
  return type;
}
