#ifndef MODEL_GAME_HPP
#define MODEL_GAME_HPP

#include <vector>

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

  /// returns true if the game has ended.
  virtual bool isOver();

  /// returns true as long as new players can be added.
  /// once the limit has been reached, returns false.
  virtual bool canAddNewPlayer();

  /// adds a new Player* to the players vector
  /// returns false if no new player has been added.
  /// (if max number of players was reached or if init failed)
  virtual bool addPlayer();

  /// increments currentplayer, modulo number of players.
  virtual void nextTurn();

  /// tries to place a tile at coordinates x y,
  /// returns false if the placement was invalid (= tile wasn't placed).
  virtual bool placeTile(Tile* const tile, int x, int y);
};

#endif