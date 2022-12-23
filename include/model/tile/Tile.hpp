#ifndef MODEL_TILE_HPP
#define MODEL_TILE_HPP

class Tile {
 private:
 public:
  Tile();
  virtual ~Tile();

  virtual void rotateClockwise() = 0;
  virtual void rotateCounterClockwise() = 0;

  /// this function must be called in the following way : tile1.matchX(tile2)
  /// with tile1 being the tile IMMEDIATELY ON THE LEFT of tile2.
  /// in other words, the X coordinate of tile1 must be exactly 1 lower than the
  /// X coordinate of tile2.
  ///
  /// returns true if the two tiles match (relative to the chosen game mode).
  virtual bool matchX(const Tile* right) const = 0;

  /// this function must be called in the following way : tile1.matchY(tile2)
  /// with tile1 being the tile IMMEDIATELY UPWARDS of tile2.
  /// in other words, the Y coordinate of tile1 must be exactly 1 lower than the
  /// Y coordinate of tile2.
  ///
  /// returns true if the two tiles match (relative to the chosen game mode).
  virtual bool matchY(const Tile* down) const = 0;
};

#endif