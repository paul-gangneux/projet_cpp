#include "model/game/GameCarcassonne.hpp"

#include <algorithm>
#include <iostream>

#include "model/tile/TileCarcassonne.hpp"

#define putInBag(type, num)                   \
  for (size_t i = 0; i < num; i++) {          \
    bag.push_back(new TileCarcassonne(type)); \
  }

GameCarcassonne::GameCarcassonne() :
    Game(),
    bag{std::vector<TileCarcassonne*>()},
    currentPlayerHasPlacedTile{false},
    lastX{0},
    lastY{0} {
  putInBag(1, 9);
  putInBag(2, 3);
  putInBag(3, 2);
  putInBag(4, 1);
  putInBag(5, 1);
  putInBag(6, 3);
  putInBag(7, 3);
  putInBag(8, 8);
  putInBag(9, 4);
  putInBag(10, 5);
  putInBag(11, 2);
  putInBag(12, 3);
  putInBag(13, 4);
  putInBag(14, 2);
  putInBag(15, 3);
  putInBag(16, 2);
  putInBag(17, 3);
  putInBag(18, 3);
  putInBag(19, 1);
  putInBag(20, 2);
  putInBag(21, 1);
  putInBag(22, 1);
  putInBag(23, 2);
  putInBag(24, 3);

  // the last tile in bag will the the first placed in game
  putInBag(17, 1);

  random_shuffle(bag.begin(), bag.end() - 1);
}

GameCarcassonne::~GameCarcassonne() {
  for (TileCarcassonne* t : bag) {
    delete t;
  }
}

bool GameCarcassonne::canAddNewPlayer() {
  return true;
}

Tile* GameCarcassonne::grabTile() {
  if (bag.empty()) {
    // --- DEBUG
    std::cout
        << std::endl
        << "OOPSIE: GameCarcassonne::grabTile() was called, but the bag is "
           "empty. Check value of isGameOver"
        << std::endl;
    std::exit(1);
    // --- end debug
  }
  Tile* res = bag.back();
  bag.pop_back();  // no, pop_back does not return anything
  return res;
}

bool GameCarcassonne::placeFirstTile(Tile* const _tile) {
  return Game::placeTile(_tile, 0, 0);
}

bool GameCarcassonne::placeTile(Tile* const _tile, int x, int y) {
  if (currentPlayerHasPlacedTile)
    return false;
  if (Game::placeTile(_tile, x, y)) {
    currentPlayerHasPlacedTile = true;
    lastX = x;
    lastY = y;
    return true;
  }
  return false;
}

bool GameCarcassonne::searchMeeple(
    tileAndDir current, std::vector<tileAndDir>* visited) {
  // first we check if the tileAndDir has already been visited.

  if (std::find((*visited).begin(), (*visited).end(), current) !=
      (*visited).end())
    return false;

  // if not, we add the current tile to the visited list.

  visited->push_back(current);

  // then, we check if it contains a meeple. if it does, the search is over.

  TileCarcassonne* local =
      dynamic_cast<TileCarcassonne*>(board.get(current.x, current.y));
  if (local == nullptr)
    return false;
  if (local->getMeepleLocation() == current.d)
    return true;

  // if we haven't found a meeple, the search continues.
  // first we need to search in the adjacent tile (relative to the dir), in the
  // appropriate dir.

  int xToVisit = current.x;
  int yToVisit = current.y;
  switch (current.d) {
    case 11:
    case 0:
    case 1:
      yToVisit--;
      break;
    case 2:
    case 3:
    case 4:
      xToVisit++;
      break;
    case 5:
    case 6:
    case 7:
      yToVisit++;
      break;
    default:
      xToVisit--;
      break;
  }
  if ((board.get(xToVisit, yToVisit) != nullptr) &&
      searchMeeple(
          tileAndDir(xToVisit, yToVisit, adjacentDir(current.d)), visited))
    return true;

  // then we need to search in the other dirs that are linked to the current
  // one, through the edges.

  std::vector<uint8_t> toVisit;
  for (TileCarcassonne::edge e : local->getEdges()) {
    // we look at all the edges of the tile, and keep the dir (vertices)
    // connected to the current dir.
    uint8_t d = e.otherSide(current.d);
    if (d != 13)
      toVisit.push_back(d);
  }

  for (uint8_t visit : toVisit) {
    if (searchMeeple(tileAndDir(current.x, current.y, visit), visited))
      return true;
  }

  return false;
}

bool GameCarcassonne::placeMeeple(int _dir) {
  if (!currentPlayerHasPlacedTile)
    return false;

  if (_dir == 13) {
    TileCarcassonne* local =
        dynamic_cast<TileCarcassonne*>(board.get(lastX, lastY));
    if (local == nullptr)
      return false;

    local->addMeeple(_dir);  // TODO : add currentplayer parameter
  }

  if (_dir != -1) {
    std::vector<tileAndDir> visited;

    if (searchMeeple(tileAndDir(lastX, lastY, _dir), &visited)) {
      // TODO : unfinished
    }
  }

  nextTurn();
  return true;
}

bool GameCarcassonne::canPlaceMeeple() {
  return currentPlayerHasPlacedTile;
}

void GameCarcassonne::nextTurn() {
  Game::nextTurn();
  currentPlayerHasPlacedTile = false;
}

uint8_t GameCarcassonne::adjacentDir(uint8_t _dir) {
  switch (_dir) {
    case 0:
    case 3:
    case 6:
    case 9:
      return (_dir + 6) % 12;
      break;
    case 1:
    case 4:
    case 7:
    case 10:
      return (_dir + 4) % 12;
      break;
    case 2:
    case 5:
    case 8:
    case 11:
      return (_dir + 8) % 12;
      break;
  }
  // this should be an unreachable statement.
  return 13;
}
