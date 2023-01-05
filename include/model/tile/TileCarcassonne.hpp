#ifndef MODEL_TILE_CARCASSONNE_HPP
#define MODEL_TILE_CARCASSONNE_HPP

#include <cstdint>
#include <vector>

#include "Tile.hpp"

class TileCarcassonne : public Tile {
 public:
  struct edge;

 private:
  /// a number telling which tile it is, relative to its position in the
  /// carcassonne rules pdf.
  uint8_t type;

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
  char border[4];

 public:
  TileCarcassonne(uint8_t);
  virtual ~TileCarcassonne();

  char getBorder(int) const;
  int8_t getMeeplePlayer() const;
  int8_t getMeepleLocation() const;
  std::vector<edge> getEdges() const;
  int getType() const;

  virtual void rotateClockwise();
  virtual void rotateCounterClockwise();

  virtual bool matchX(const Tile* right) const;
  virtual bool matchY(const Tile* down) const;

  bool addMeeple(int _dir, int player);
  void removeMeeple();

  bool hasMonastery() const;

  /// a pair of numbers : "low" and "high"
  /// we always have low <= high.
  struct edge {
    uint8_t low;
    uint8_t high;

    edge(uint8_t a, uint8_t b);

    void rotateClockwise();
    void rotateCounterClockwise();

    // function name is a bit confusing, but i couldn't find a better one.

    /// If the edge has the value "a", returns the other value.
    /// otherwise, returns 13.
    uint8_t otherSide(uint8_t a);
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
};

#endif