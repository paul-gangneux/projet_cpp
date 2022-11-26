#ifndef MODEL_GAME_HPP
#define MODEL_GAME_HPP

#include "Player.hpp"
#include "Board.hpp"

class Game {
private:
    Player* players;
    Board board;
    std::vector<Tile*> bag;
public:
  Game();
  virtual ~Game();  
  
};

#endif