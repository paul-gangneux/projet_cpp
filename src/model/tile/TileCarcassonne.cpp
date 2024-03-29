#include "model/tile/TileCarcassonne.hpp"

#include <iostream>
#include <string>

#define DIR(a)          \
  {                     \
    border[0] = (a)[0]; \
    border[1] = (a)[1]; \
    border[2] = (a)[2]; \
    border[3] = (a)[3]; \
  }

#define EDGE(a, b) edges.push_back(edge(a, b));

TileCarcassonne::TileCarcassonne(uint8_t _type) :
    type{_type},
    edges{std::vector<edge>()},
    monastery{false},
    meeplePlayer{-1},
    meepleLocation{-1} {
  switch (type) {
      // TODO : check if all the cases are correctly written. they should be
      // fine, though
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
      // EDGE(3, 9)  // redundant
      // indeed there are redundant edges, all we need is a connex graph for
      // related borders, it doesn't need to be a complete graph
      break;
    case 5:
      DIR("Ttgt")
      EDGE(0, 3)
      EDGE(0, 9)
      // EDGE (3, 9) // redundant
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
      EDGE(10, 2)
      EDGE(4, 5)
      EDGE(7, 8)
      // the roads are not connected since there is a crossroads.
      break;
    case 8:
      DIR("rgrg")
      EDGE(0, 6);
      EDGE(1, 3);
      EDGE(3, 5);
      // EDGE(1, 5);  // redundant
      EDGE(7, 9);
      EDGE(9, 11);
      // EDGE(11, 7);  // redundant
      break;
    case 9:
      DIR("grrr")  // angry tile haha
      EDGE(0, 2);
      EDGE(0, 10);
      // EDGE(10, 2);  // redundant
      EDGE(4, 5)
      EDGE(7, 8)
      break;
    case 10:
      DIR("tggg")
      EDGE(3, 6)
      EDGE(6, 9)
      // EDGE(9,3) // redundant
      break;
    case 11:
      DIR("ttgg")
      EDGE(6, 9)
      break;
    case 12:
      DIR("ttgt")
      EDGE(0, 3)
      EDGE(0, 9)
      // EDGE(3,9) //redundant
      break;
    case 13:
      DIR("gggg")
      monastery = true;
      EDGE(0, 3)
      EDGE(3, 6)
      EDGE(6, 9)
      EDGE(9, 0)
      // EDGE(0, 6)  // redundant
      // EDGE(3, 9)  // redundant
      break;
    case 14:
      DIR("ggrg")
      monastery = true;
      EDGE(0, 3)
      EDGE(3, 5)
      EDGE(7, 9)
      EDGE(9, 0)
      // EDGE(0,5) // all redundant
      // EDGE(0,7)
      // EDGE(5,7)
      // EDGE(5,9)
      // EDGE(7,3)
      // EDGE(3,9)
      break;
    case 15:
      DIR("tggt")
      EDGE(0, 9)
      EDGE(3, 6)
      break;
    case 16:
      DIR("gTgt")
      EDGE(3, 9)
      break;
    case 17:
      DIR("trgr")
      EDGE(3, 9)
      EDGE(2, 10)
      EDGE(4, 6)
      EDGE(6, 8)
      // EDGE(4,8) // redundant
      break;
    case 18:
      DIR("tgrr")
      EDGE(6, 9)
      EDGE(3, 5)
      EDGE(10, 3)
      EDGE(7, 8)
      // EDGE(5,10) // redundant
      break;
    case 19:
      DIR("gtgt")
      EDGE(3, 9)
      break;
    case 20:
      DIR("Ttrt")
      EDGE(0, 3)
      EDGE(9, 0)
      // EDGE(3,9) // redundant
      break;
    case 21:
      DIR("Tttt")
      EDGE(0, 3)
      EDGE(3, 6)
      EDGE(6, 9)
      EDGE(9, 0)
      // EDGE(0, 6) // redundant
      // EDGE(3, 9) // redundant
      break;
    case 22:
      DIR("rrrr")
      EDGE(1, 2)
      EDGE(4, 5)
      EDGE(7, 8)
      EDGE(10, 11)
      break;
    case 23:
      DIR("Tggt")
      EDGE(3, 6)
      EDGE(9, 0)
      break;
    case 24:
      DIR("gtgt")
      EDGE(0, 6)
      break;
  }
}

TileCarcassonne::~TileCarcassonne() {
  // nothing to do
}

void TileCarcassonne::rotateClockwise() {
  int temp = border[3];
  border[3] = border[2];
  border[2] = border[1];
  border[1] = border[0];
  border[0] = temp;
  for (edge& e : edges) {
    e.rotateClockwise();
  }

  if (meepleLocation != -1 && meepleLocation != 13)
    meepleLocation = (meepleLocation + 3) % 12;
}

void TileCarcassonne::rotateCounterClockwise() {
  int temp = border[0];
  border[0] = border[1];
  border[1] = border[2];
  border[2] = border[3];
  border[3] = temp;

  for (edge& e : edges) {
    e.rotateCounterClockwise();
  }

  if (meepleLocation != -1 && meepleLocation != 13)
    meepleLocation = (meepleLocation + 9) % 12;
}

std::vector<TileCarcassonne::edge> TileCarcassonne::getEdges() const {
  return edges;
}

char TileCarcassonne::getBorder(int a) const {
  if (a < 0)
    return border[0];
  // technically we should only call this function with a value between 0 and 3,
  // but just in case:
  return border[a % 4];
}

int8_t TileCarcassonne::getMeeplePlayer() const {
  return meeplePlayer;
}

int8_t TileCarcassonne::getMeepleLocation() const {
  return meepleLocation;
}

bool TileCarcassonne::matchX(const Tile* right) const {
  const TileCarcassonne* local = dynamic_cast<const TileCarcassonne*>(right);
  if (local == nullptr)
    return false;

  return (tolower(border[1]) == tolower(local->getBorder(3)));
}

bool TileCarcassonne::matchY(const Tile* down) const {
  const TileCarcassonne* local = dynamic_cast<const TileCarcassonne*>(down);
  if (local == nullptr)
    return false;

  return (tolower(border[2]) == tolower(local->getBorder(0)));
}

int TileCarcassonne::getType() const {
  return type;
}

bool TileCarcassonne::addMeeple(int _dir, int player) {
  if (meeplePlayer != -1)
    return false;

  if (_dir == 13 && !monastery) {
    return false;
  }

  meepleLocation = _dir;
  meeplePlayer = player;
  return true;
}

void TileCarcassonne::removeMeeple() {
  meepleLocation = -1;
  meeplePlayer = -1;
}

bool TileCarcassonne::hasMonastery() const {
  return monastery;
}

// =============================================== //
// --- definition of functions for struct edge --- //
// =============================================== //

TileCarcassonne::edge::edge(uint8_t a, uint8_t b) : low{a}, high{b} {
  if (b < a) {
    low = b;
    high = a;
  }
}

void TileCarcassonne::edge::rotateClockwise() {
  low = (low + 3) % 12;
  high = (high + 3) % 12;
  if (high < low) {
    uint8_t temp = low;
    low = high;
    high = temp;
  }
}

void TileCarcassonne::edge::rotateCounterClockwise() {
  low = (low + 9) % 12;
  high = (high + 9) % 12;
  if (high < low) {
    uint8_t temp = low;
    low = high;
    high = temp;
  }
}

// function name is a bit confusing, but i couldn't find a better one.

/// If the edge has the value "a", returns the other value.
/// otherwise, returns 13.
uint8_t TileCarcassonne::edge::otherSide(uint8_t a) {
  if (low == a)
    return high;
  if (high == a)
    return low;
  return 13;
}
