#ifndef MODEL_TILE_HPP
#define MODEL_TILE_HPP

class Tile {
private:

public:
  Tile();
  virtual ~Tile();

  virtual void rotateClockwise() = 0;
  virtual void rotateCounterClockwise() = 0;

  virtual bool matchX(Tile* right) = 0;
  virtual bool matchY(Tile* down) = 0;
};

#endif