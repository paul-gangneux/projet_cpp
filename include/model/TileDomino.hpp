#ifndef MODEL_TILE_DOMINO_HPP
#define MODEL_TILE_DOMINO_HPP

#include "Tile.hpp"

class TileDomino : public Tile{
  private:
    /*
    Here is how we will represent the Domino Tile :
    Using four int arrays of length 3.

    ++ T0 T1 T2 ++    T : "Top"
    L2          R0    R : "Right"
    L1          R1    L : "Left"
    L0          R2    B : "Bottom"
    ++ B2 B1 B0 ++

    As pictured, the array numbers will count clockwise.
    This will help for rotation & placement operations.

    NOTE: don't shoot me paul, we can switch to a single array of size 12 if you prefer
    */
    int* T;
    int* R;
    int* B;
    int* L;

    void generate3ForArray(int*);

  public:
    TileDomino();
    virtual ~TileDomino();
  
    void rotateClockwise();
    void rotateCounterClockwise();
};

#endif