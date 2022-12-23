#ifndef MODEL_GAME_HPP
#define MODEL_GAME_HPP

#include <vector>
#include "model/Board.hpp"
#include "model/Player.hpp"

#include "model/Board.hpp"
#include "model/Player.hpp"

class Game {
 protected:
  std::vector<Player*> players;
  Board board;
  int currentPlayer;
  bool firstPlay;
  bool gameIsOver;

 public:
  Game();
  virtual ~Game();

  std::vector<Player*> const getPlayers() const;

  // must return true if game is over
  bool isOver();

  virtual bool canAddNewPlayer();
  bool addPlayer();

  // virtual Tile* grabTile() = 0;
  // takes a tile from the bag. i named it "grab" to avoid using "get" or "draw"
  // not all games have bags
  void nextTurn();

  virtual bool placeTile(Tile* const tile, int x, int y);
};

#endif