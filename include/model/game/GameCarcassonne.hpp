#ifndef MODEL_GAME_CARCASSONE_HPP
#define MODEL_GAME_CARCASSONE_HPP

#include <queue>

#include "model/game/Game.hpp"
#include "model/tile/TileCarcassonne.hpp"

class GameCarcassonne : public Game {
 private:
  /// contains all the tiles that will be played
  /// during the game. once it is empty, the game is over.
  std::vector<TileCarcassonne*> bag;
  bool currentPlayerHasPlacedTile;
  int lastX;
  int lastY;

  // contains info of meeples to be removed from view
  // infos are: tile position x, tile position y, direction
  std::queue<int*> removedMeepleQueue;

  /// saves the coordinates of a tile, and one direction {0,...,11}.
  /// will be used in our algorithms.
  struct tileAndDir {
    int x;
    int y;
    uint8_t d;

    tileAndDir(int _x, int _y, uint8_t _d);

    bool operator==(tileAndDir b) const;
  };

  struct meepleInfo {
    int x, y, dir, player;
  };

  /// does a complete search of the graph.
  /// stops the search at any point if the stop condition is met,
  /// returns true if the stop condition has been met, false otherwise
  ///
  /// if nbVisited != nullptr, it will store the number of existing tiles
  /// visited
  ///
  /// if meepInfos != nullptr, it will store the data about all the meeples
  /// found during the search as a queue of [pos x, pos y, direction, player]
  bool searchGraph(
      tileAndDir current,
      std::vector<tileAndDir>& visited,
      int* nbVisited = nullptr,
      int* nbOfShields = nullptr,
      std::queue<meepleInfo>* meepInfos = nullptr,
      int stopCondition = 0);

  /// initializes the vector of marked vertices
  /// shouldn't be called recursively
  bool searchGraph(
      tileAndDir current,
      int* nbVisited = nullptr,
      int* nbOfShields = nullptr,
      std::queue<meepleInfo>* meepInfos = nullptr,
      int stopCondition = 0);

  int countNeighbors(int x, int y);

  void calculateNewScores();

  void endGameCalculations();

  void calculateScoresIncomplete();

  /// returns the adjacent dir number of the adjacent tile.
  /// for example, if _dir=2, then the function returns 10, as the adjacent dir
  /// would be 10 on the tile on the right.
  uint8_t adjacentDir(uint8_t _dir);

 public:
  GameCarcassonne(int nb_of_players);
  virtual ~GameCarcassonne();

  virtual bool canAddNewPlayer();

  /// returns a Tile* from the bag.
  /// however, it points to a TileCarcassonne, so we will use casting later.
  virtual Tile* grabTile();

  /// tries to place a tile at coordinates x y,
  /// returns false if the placement was invalid (= tile wasn't placed).
  ///
  /// if the tile was placed correctly : returns true,
  /// checks if the bag is empty - if it is, changes gameIsOver to true
  virtual bool placeTile(Tile* const, int x, int y);

  bool placeFirstTile(Tile* const _tile);

  virtual void nextTurn();

  // places meeple on last placed tile
  // returns the dir where the meeple has actually been placed and calls
  // nextTurn if successful
  // if dir == -1, does nothing, calls nextTurn and returns 14
  // returns -1 on failure
  int placeMeeple(int _dir);

  bool canPlaceMeeple();

  bool getLastRemovedMeepleInfo(int infos[3]);
};

#endif