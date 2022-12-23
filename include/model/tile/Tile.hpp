#ifndef MODEL_TILE_HPP
#define MODEL_TILE_HPP

class Tile {
 private:
 public:
  Tile();
  virtual ~Tile();

  virtual void rotateClockwise() = 0;
  virtual void rotateCounterClockwise() = 0;

  virtual bool matchX(const Tile* right) const = 0;
  virtual bool matchY(const Tile* down) const = 0;
};

#endif