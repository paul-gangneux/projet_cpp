#ifndef MODEL_TILE_CARCASSONNE_HPP
#define MODEL_TILE_CARCASSONNE_HPP

#include <cstdint>
#include <vector>

#include "Tile.hpp"

class TileCarcassonne : public Tile {
 private:
  /// a number telling which tile it is, relative to its position in the
  /// carcassonne rules pdf.
  uint8_t type;

  /// a pair of numbers : "low" and "high"
  /// we always have low <= high.
  struct edge {
    uint8_t low;
    uint8_t high;

    edge(uint8_t a, uint8_t b) : low{a}, high{b} {
      if (b < a) {
        low = b;
        high = a;
      }
    }

    void rotateClockwise() {
      low = (low + 3) % 12;
      high = (high + 3) % 12;
      if (high < low) {
        uint8_t temp = low;
        low = high;
        high = temp;
      }
    }

    void rotateCounterClockwise() {
      low = (low + 9) % 12;
      high = (high + 9) % 12;
      if (high < low) {
        uint8_t temp = low;
        low = high;
        high = temp;
      }
    }
  };
  /*
  The numbers on the edges need to be more precise than the ones for dir.
  Here is their representation :
  ++ 11  0  1  ++
  10            2
  9             3
  8             4    You may think of it as a clock :
  ++  7  6  5  ++    0 is upwards, 3 is right, 6 is downwards...
  */

  std::vector<edge> edges;

  /// true if the tile contains a monastery
  bool monastery;

  /// the number of the player who placed this meeple.
  /// if no meeple has been placed, its value -1.
  int8_t meeplePlayer;

  /// the location of the meeple on the tile, relative to the dir array.
  /// it can be chosen arbitrarily (for example, if the tile has single road on
  /// the bottom and right side, and a meeple was placed on it, the value of
  /// meepleLocation can be 3(right) or 6(down).
  /// if no meeple has been placed, its value is -1.
  /// if the meeple is in a monastery, its value is 13.
  int8_t meepleLocation;

  /// represents what is on the borders of the tile.
  /// 0:up, 1:right, 2:down, 3:left
  /// 't':town, 'r':road, 'g':grasslands, 'T':town with shield symbol
  char dir[4];

 public:
  TileCarcassonne(uint8_t);
  virtual ~TileCarcassonne();

  char getDir(int) const;

  void rotateClockwise();
  void rotateCounterClockwise();

  bool matchX(const Tile* right) const;
  bool matchY(const Tile* down) const;

  int getType() const;
};

#endif