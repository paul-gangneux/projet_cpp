#ifndef MODEL_BOARD_HPP
#define MODEL_BOARD_HPP
#include "Tile.hpp"

#include <vector>

class Board {
private:
  std::vector<std::vector<Tile*>> board;
public:
  Board();
  virtual ~Board();

  bool placeTile(int x, int y, Tile const * const);
  

};

#endif