#ifndef MODEL_TILE_DOMINO_HPP
#define MODEL_TILE_DOMINO_HPP

#include "Tile.hpp"

class TileDomino : public Tile {
 private:
  /*
  Here is how we will represent the Domino Tile :
  Using one int array T of length 12, named "numbers"

  ++ T0 T1 T2 ++
  T11         T3
  T10         T4
  T9          T5
  ++ T8 T7 T6 ++

  As pictured, the array numbers will count CLOCKWISE, starting TOP LEFT.
  This will help for rotation & placement operations.
  */
  int* numbers;

 public:
  TileDomino();
  virtual ~TileDomino();

  int const* getNumbers() const;

  void rotateClockwise();
  void rotateCounterClockwise();

  /// checks if the 3 numbers on the right side of the current tile match
  /// with the 3 numbers on the left side of the tile "right".
  bool matchX(const Tile* right) const;

  /// checks if the 3 numbers on the bottom side of the current tile match
  /// with the 3 numbers on the top side of the tile "down".
  bool matchY(const Tile* down) const;
};

#endif