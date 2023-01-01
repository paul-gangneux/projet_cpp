#include "model/game/GameCarcassonne.hpp"
#include <algorithm>
#include <iostream>
#include <list>
#include "model/tile/TileCarcassonne.hpp"

using namespace std;

#define LOG(x) cout << x << endl

#define STOPCOND_NONE 0
#define STOPCOND_MEEPLEFOUND 1
#define STOPCOND_NOTCOMPLETE 0b10

#define putInBag(type, num)                   \
  for (size_t i = 0; i < num; i++) {          \
    bag.push_back(new TileCarcassonne(type)); \
  }

GameCarcassonne::GameCarcassonne() :
    Game(),
    bag{vector<TileCarcassonne*>()},
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

  // we shuffle every tile except the last one
  random_shuffle(bag.begin(), bag.end() - 1);
}

GameCarcassonne::~GameCarcassonne() {
  for (TileCarcassonne* t : bag) {
    delete t;
  }
  while (!removedMeepleQueue.empty()) {
    int* i = removedMeepleQueue.front();
    removedMeepleQueue.pop();
    delete[] i;
  }
}

bool GameCarcassonne::canAddNewPlayer() {
  return players.size() < 4;
}

Tile* GameCarcassonne::grabTile() {
  if (bag.empty()) {
    // --- DEBUG
    LOG("OOPSIE: GameCarcassonne::grabTile() was called, but the bag is "
        "empty. Check value of isGameOver");
    exit(1);
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

// initializes the vector of marked vertices
// shouldn't be called recursively
bool GameCarcassonne::searchGraph(
    tileAndDir current,
    int* nbVisited,
    std::queue<meepleInfo>* meepInfos,
    int stopCond) {
  vector<tileAndDir> visited;  // init empty vector
  return searchGraph(current, visited, nbVisited, meepInfos, stopCond);
}

// does a complete search of the graph.
// stops the search at any point if the stop condition is met,
// returns true if the stop condition has been met, false otherwise
//
// if nbVisited != nullptr, it will store the number of existing tiles visited
//
// if meepInfos != nullptr, it will store the data about all the meeples
// found during the search as a queue of [pos x, pos y, direction, player]
bool GameCarcassonne::searchGraph(
    tileAndDir current,
    vector<tileAndDir>& visited,
    int* nbVisited,
    queue<meepleInfo>* meepInfos,
    int stopCond) {
  // first we check if the tileAndDir has already been visited.
  if (find(visited.begin(), visited.end(), current) != visited.end()) {
    return false;
  }

  // if not, we add the current tile to the visited list.
  visited.push_back(current);

  // we check if the tile exists
  TileCarcassonne* local =
      dynamic_cast<TileCarcassonne*>(board.get(current.x, current.y));
  if (local == nullptr) {
    // the area is not complete, the search is over.
    if (stopCond == STOPCOND_NOTCOMPLETE) {
      return true;
    } else {
      return false;
    }
  }

  // if it does, increments nbVisited
  if (nbVisited != nullptr) {
    (*nbVisited)++;
  }

  // then, we check if it contains a meeple.
  if (local->getMeepleLocation() == current.d) {
    if (stopCond == STOPCOND_MEEPLEFOUND) {
      // a meeple has been found, the search is over.
      return true;
    }
    if (meepInfos != nullptr) {
      // adding infos about the found meeple to the queue
      meepInfos->push(
          {current.x, current.y, current.d, local->getMeeplePlayer()});
    }
  }

  // if not fail condition has been met, the search continues
  // first we need to search in the adjacent tile (relative to the dir), in
  // the appropriate dir.

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
      searchGraph(
          tileAndDir(xToVisit, yToVisit, adjacentDir(current.d)),
          visited,
          nbVisited,
          meepInfos,
          stopCond)) {
    return true;
  }

  // then we need to search in the other dirs that are linked to the current
  // one, through the edges.

  vector<uint8_t> toVisit;
  for (TileCarcassonne::edge e : local->getEdges()) {
    // we look at all the edges of the tile, and keep the dir (vertices)
    // connected to the current dir.
    uint8_t d = e.otherSide(current.d);
    if (d != 13) {
      toVisit.push_back(d);
    }
  }

  for (uint8_t visit : toVisit) {
    if (searchGraph(
            tileAndDir(current.x, current.y, visit),
            visited,
            nbVisited,
            meepInfos,
            stopCond)) {
      return true;
    }
  }
  return false;
}

int roundDir(int d) {
  if (d == 11 || d <= 1) {
    return 0;
  }
  if (d <= 4) {
    return 3;
  }
  if (d <= 7) {
    return 6;
  }
  return 9;
}

int GameCarcassonne::countNeighbors(int x, int y) {
  Tile* tile;
  int n = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i != 0 || j != 0) {
        tile = board.get(x + i, y + j);
        if (tile != nullptr)
          n++;
      }
    }
  }
  return n;
}

void GameCarcassonne::calculateNewScores() {
  TileCarcassonne* lastTile = (TileCarcassonne*) board.get(lastX, lastY);
  TileCarcassonne* tile;
  // checking for finished monastery
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      tile = (TileCarcassonne*) board.get(lastX + i, lastY + j);
      // now we check is the tile exists, has a monastery,
      // has a meeple on it, and is complete
      if (tile != nullptr && tile->hasMonastery() &&
          tile->getMeepleLocation() == 13 &&
          countNeighbors(lastX + i, lastY + j) == 8) {
        // player gets points
        players.at(tile->getMeeplePlayer())->addScore(9);
        // we remove the meeple from model and view
        removedMeepleQueue.push(new int[3]{lastX + i, lastY + j, 13});
        tile->addMeeple(-1, -1);
      }
    }
  }
}

bool GameCarcassonne::placeMeeple(int _dir) {
  if (!currentPlayerHasPlacedTile)
    return false;

  TileCarcassonne* local =
      dynamic_cast<TileCarcassonne*>(board.get(lastX, lastY));
  if (local == nullptr) {
    return false;
  }

  if (_dir == 13) {
    if (!local->addMeeple(_dir, currentPlayer)) {
      return false;
    }
  }

  else if (_dir != -1) {
    int tmp = _dir + 1;
    if (tmp == 12) {
      tmp = 0;
    }
    tmp /= 3;
    if (local->getDir(tmp) != 'r') {
      _dir = roundDir(_dir);
    }

    if (searchGraph(
            tileAndDir(lastX, lastY, _dir),
            nullptr,
            nullptr,
            STOPCOND_MEEPLEFOUND)) {
      return false;
    }
    if (!local->addMeeple(_dir, currentPlayer)) {
      return false;
    }
  }

  calculateNewScores();
  nextTurn();
  return true;
}

bool GameCarcassonne::canPlaceMeeple() {
  return currentPlayerHasPlacedTile;
}

void GameCarcassonne::nextTurn() {
  if (bag.empty()) {
    gameIsOver = true;
    // TODO: calculate end game scores
  } else {
    Game::nextTurn();
  }
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

bool GameCarcassonne::getLastRemovedMeepleInfo(int infos[3]) {
  if (removedMeepleQueue.empty()) {
    return false;
  }
  int* meep = removedMeepleQueue.front();
  infos[0] = meep[0];
  infos[1] = meep[1];
  infos[2] = meep[2];
  removedMeepleQueue.pop();
  delete[] meep;
  return true;
}
