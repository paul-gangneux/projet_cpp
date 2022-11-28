#ifndef MODEL_TILE_DOMINO_HPP
#define MODEL_TILE_DOMINO_HPP

#include "Tile.hpp"

class TileDomino : public Tile{
  private:
    /*
    Here is how we will represent the Domino Tile :
    Using one int array T of length 12.

    ++ T0 T1 T2 ++
    T11         T3
    T10         T4
    T9          T5
    ++ T8 T7 T6 ++

    As pictured, the array numbers will count CLOCKWISE, starting TOP LEFT.
    This will help for rotation & placement operations.
    */
    int* T;
  public:
    TileDomino();
    virtual ~TileDomino();
  
    void rotateClockwise();
    void rotateCounterClockwise();
};

#endif