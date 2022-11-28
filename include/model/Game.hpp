#ifndef MODEL_GAME_HPP
#define MODEL_GAME_HPP

#include "Player.hpp"
#include "Board.hpp"

class Game {
private:
  Player* players;
  Board board;

  virtual void gameOver() = 0;
public:
  Game();
  virtual ~Game();

  virtual Tile* grabTile() = 0;//takes a tile from the bag. i named it "grab" to avoid using "get" or "draw"
};

#endif