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
  int nbOfPlacedTiles;
  int nbOfDiscardedTiles;
  int maxNbOfTiles;

 public:
  // Game();
  Game(const char* p1name, const char* p2name, int nb_of_tiles);
  Game(int nb_of_players, int nb_of_tiles);
  virtual ~Game();

  const std::vector<Player*>& getPlayers() const;

  Player const* getCurrentPlayer() const;

  int getCurrentPlayerIndex() const;

  /// returns true if the game has ended.
  virtual bool isOver();

  /// returns true as long as new players can be added.
  /// once the limit has been reached, returns false.
  virtual bool canAddNewPlayer();

  /// adds a new Player* to the players vector
  /// returns false if no new player has been added.
  /// (if max number of players was reached or if init failed)
  virtual bool addPlayer();

  virtual bool addPlayer(const char* name);
  virtual bool addPlayer(const std::string name);

  /// increments currentplayer, modulo number of players.
  virtual void nextTurn();

  /// tries to place a tile at coordinates x y,
  /// returns false if the placement was invalid (= tile wasn't placed).
  virtual bool placeTile(Tile* const tile, int x, int y);

  int nbOfTilesLeft();
};

#endif