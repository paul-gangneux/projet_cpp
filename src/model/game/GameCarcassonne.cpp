#include "model/game/GameCarcassonne.hpp"
#include <algorithm>
#include <iostream>
#include <list>
#include "model/tile/TileCarcassonne.hpp"

using namespace std;

#define LOG(x) cout << x << endl;

#define STOPCOND_NONE 0
#define STOPCOND_MEEPLEFOUND 1
#define STOPCOND_NOTCOMPLETE 2

#define putInBag(type, num)                   \
  for (size_t i = 0; i < num; i++) {          \
    bag.push_back(new TileCarcassonne(type)); \
  }

#define addIfNotExist(collection, item)                                       \
  if (find(collection.begin(), collection.end(), item) == collection.end()) { \
    collection.push_back(item);                                               \
  }

/// Used in endGameCalculations() for the breadth-first search.
/// basically, checks if there is a tile on the board at (x,y),
/// and if so, checks if it wasn't already visited (if it isn't in the vector v)
/// if so : adds it to the bfs queue, and marks it as visited for the bfs
#define BFS_NEIGHBOR(x, y)                                    \
  neighbor = tileAndDir(x, y, 0);                             \
  if ((board.get(x, y) != nullptr) &&                         \
      (std::find(v.begin(), v.end(), neighbor) == v.end())) { \
    q.push(neighbor);                                         \
    v.push_back(neighbor);                                    \
  }

static const char* defaultPlayerNames[]{"yellow", "red", "blue", "green"};

GameCarcassonne::GameCarcassonne(int nb_of_players) :
    Game(nb_of_players, 72),
    bag{vector<TileCarcassonne*>()},
    currentPlayerHasPlacedTile{false},
    lastX{0},
    lastY{0},
    meepleVector{vector<int>(nb_of_players)} {
  for (int i = 0; i < nb_of_players; i++) {
    players[i]->setName(defaultPlayerNames[i]);
    meepleVector[i] = 6;
  }

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
    if (meepleVector[currentPlayer] <= 0) {
      nextTurn();
    }
    return true;
  }
  return false;
}

// initializes the vector of marked vertices
// shouldn't be called recursively
bool GameCarcassonne::searchGraph(
    tileAndDir current,
    int* nbVisited,
    int* nbOfShields,
    std::queue<meepleInfo>* meepInfos,
    int stopCond) {
  vector<tileAndDir> visited;  // init empty vector
  return searchGraph(
      current, visited, nbVisited, nbOfShields, meepInfos, stopCond);
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
    int* nbOfShields,
    queue<meepleInfo>* meepInfos,
    int stopCond) {
  // first we check if the tileAndDir has already been visited.
  if (find(visited.begin(), visited.end(), current) != visited.end()) {
    return false;
  }

  // if not, we check id the tile itself has been visited before,
  // and increment nbVisited accordingly
  if (nbVisited != nullptr) {
    bool shouldincrement = true;
    for (tileAndDir data : visited) {
      if (data.x == current.x && data.y == current.y) {
        shouldincrement = false;
        break;
      }
    }
    if (shouldincrement) {
      (*nbVisited)++;
    }
  }

  // then, we add the current tile to the visited list.
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

  // checks is current dir is a city with a shield
  if (nbOfShields != nullptr) {
    int newDir = -1;
    if (current.d == 0) {
      newDir = 0;
    } else if (current.d == 3) {
      newDir = 1;
    } else if (current.d == 6) {
      newDir = 2;
    } else if (current.d == 9) {
      newDir = 3;
    }
    if (newDir != -1 && local->getBorder(newDir) == 'T') {
      (*nbOfShields)++;
    }
  }

  // checks if currrent dir contains a meeple.
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
  if ((board.get(xToVisit, yToVisit) != nullptr)) {
    if (searchGraph(
            tileAndDir(xToVisit, yToVisit, adjacentDir(current.d)),
            visited,
            nbVisited,
            nbOfShields,
            meepInfos,
            stopCond)) {
      return true;
    }
  } else {
    if (stopCond == STOPCOND_NOTCOMPLETE) {
      return true;
    }
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
            nbOfShields,
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

int dirToBorder(int d) {
  d = roundDir(d);
  if (d == 0) {
    return 0;
  } else if (d == 3) {
    return 1;
  } else if (d == 6) {
    return 2;
  }
  return 3;
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
        int playerNb = tile->getMeeplePlayer();
        players.at(playerNb)->addScore(9);
        // we remove the meeple from model and view
        meepleVector[playerNb]++;
        removedMeepleQueue.push(new int[3]{lastX + i, lastY + j, 13});
        tile->removeMeeple();
      }
    }
  }

  TileCarcassonne* lastTile = (TileCarcassonne*) board.get(lastX, lastY);

  // checking for complete road or city
  for (int i = 0; i <= 3; i++) {
    uint8_t d = i * 3;
    char terrainType = lastTile->getBorder(i);
    int nbVisited = 0;
    int nbShields = 0;
    int* nbShields_p;
    int mult;
    queue<meepleInfo> meepInfos;
    if (terrainType == 'r' || terrainType == 't' || terrainType == 'T') {
      if (terrainType == 'r') {
        nbShields_p = nullptr;
        mult = 1;
      } else {
        nbShields_p = &nbShields;
        mult = 2;
      }

      // we only calculate the score if the road or town is complete
      if (!searchGraph(
              tileAndDir{lastX, lastY, d},
              &nbVisited,
              nbShields_p,
              &meepInfos,
              STOPCOND_NOTCOMPLETE) &&
          nbVisited > 0) {
        // the rules stipulate that cities of size two are worth only 2 points
        if (terrainType != 'r' && nbVisited == 2) {
          nbVisited = 1;
        }

        // we calculate all the players who deserve to get points
        // at the same time, we remove the meeples from model and view
        int nbOfPlayers = players.size();
        int* meeplePerPlayer = new int[nbOfPlayers];
        for (int j = 0; j < nbOfPlayers; j++) {
          meeplePerPlayer[j] = 0;
        }
        while (!meepInfos.empty()) {
          meepleInfo mi = meepInfos.front();
          meeplePerPlayer[mi.player]++;

          // removing meeple from model and view
          meepleVector[mi.player]++;
          removedMeepleQueue.push(new int[3]{mi.x, mi.y, mi.dir});
          ((TileCarcassonne*) board.get(mi.x, mi.y))->removeMeeple();
          meepInfos.pop();
        }
        int max = 0;
        for (int j = 0; j < nbOfPlayers; j++) {
          if (max < meeplePerPlayer[j]) {
            max = meeplePerPlayer[j];
          }
        }
        if (max > 0) {
          for (int j = 0; j < nbOfPlayers; j++) {
            if (meeplePerPlayer[j] == max) {
              players.at(j)->addScore(nbVisited * mult + 2 * nbShields);
            }
          }
        }
        delete[] meeplePerPlayer;
      }
    }
  }
}

void GameCarcassonne::calculateEndScoresFromMeeple(meepleInfo meep) {
  TileCarcassonne* tile = (TileCarcassonne*) board.get(meep.x, meep.y);

  // case monastery
  if (meep.dir == 13) {
    if (tile != nullptr && tile->hasMonastery()) {
      players.at(meep.player)->addScore(countNeighbors(meep.x, meep.y) + 1);

      // we remove the meeple from model only (not view)
      tile->removeMeeple();
    }
  }

  // case city or road
  else {
    char terrainType = tile->getBorder(dirToBorder(meep.dir));
    int nbVisited = 0;
    int nbShields = 0;
    int* nbShields_p;
    queue<meepleInfo> meepInfos;
    if (terrainType == 'r' || terrainType == 't' || terrainType == 'T') {
      if (terrainType == 'r') {
        nbShields_p = nullptr;
      } else {
        nbShields_p = &nbShields;
      }

      searchGraph(
          tileAndDir{meep.x, meep.y, (uint8_t) meep.dir},
          &nbVisited,
          nbShields_p,
          &meepInfos,
          STOPCOND_NONE);

      // we calculate all the players who deserve to get points
      // at the same time, we remove the meeples from model (not view)
      int nbOfPlayers = players.size();
      int* meeplePerPlayer = new int[nbOfPlayers];
      for (int j = 0; j < nbOfPlayers; j++) {
        meeplePerPlayer[j] = 0;
      }
      while (!meepInfos.empty()) {
        meepleInfo mi = meepInfos.front();
        meeplePerPlayer[mi.player]++;

        // removing meeple from model (not view)
        ((TileCarcassonne*) board.get(mi.x, mi.y))->removeMeeple();
        meepInfos.pop();
      }
      int max = 0;
      for (int j = 0; j < nbOfPlayers; j++) {
        if (max < meeplePerPlayer[j]) {
          max = meeplePerPlayer[j];
        }
      }
      if (max > 0) {
        for (int j = 0; j < nbOfPlayers; j++) {
          if (meeplePerPlayer[j] == max) {
            players.at(j)->addScore(nbVisited + nbShields);
          }
        }
      }
      delete[] meeplePerPlayer;
    }
  }
}

// returns the dir where the meeple has actually been placed
// returns 14 if the meeple has been successfully yeeted
// returns -1 on failure
int GameCarcassonne::placeMeeple(int dir) {
  if (!currentPlayerHasPlacedTile || meepleVector[currentPlayer] <= 0)
    return -1;

  TileCarcassonne* local =
      dynamic_cast<TileCarcassonne*>(board.get(lastX, lastY));
  if (local == nullptr) {
    return -1;
  }

  if (dir == 13) {
    if (!local->addMeeple(dir, currentPlayer)) {
      return -1;
    }
  }

  else if (dir != -1) {
    int tmp = dir + 1;
    if (tmp == 12) {
      tmp = 0;
    }
    tmp /= 3;
    if (local->getBorder(tmp) != 'r') {
      dir = roundDir(dir);
    }

    if (searchGraph(
            tileAndDir(lastX, lastY, (uint8_t) dir),
            nullptr,
            nullptr,
            nullptr,
            STOPCOND_MEEPLEFOUND)) {
      return -1;
    }
    if (!local->addMeeple(dir, currentPlayer)) {
      return -1;
    }
    meepleVector[currentPlayer]--;
  }

  calculateNewScores();
  nextTurn();
  if (dir == -1) {
    dir = 14;
  }
  return dir;
}

void GameCarcassonne::addToLocalCompletedCities(
    vector<tileAndDir>& localCityReps, tileAndDir v, int border) {
  TileCarcassonne* t = (TileCarcassonne*) board.get(v.x, v.y);
  int dir = border * 3;
  if ((v.d == (dir + 2) % 12 || v.d == (dir + 3) % 12 ||
       v.d == (dir + 9) % 12 || v.d == (dir + 10) % 12) &&
      (t->getBorder(border) == 't' || t->getBorder(border) == 'T')) {
    tileAndDir td{v.x, v.y, (uint8_t) dir};

    vector<tileAndDir> cityVisited = vector<tileAndDir>();
    if (!searchGraph(
            td, cityVisited, nullptr, nullptr, nullptr, STOPCOND_NOTCOMPLETE)) {
      // fetching the min visited tileAndDir
      tileAndDir minCityTile = td;
      for (tileAndDir city_td : cityVisited) {
        if (city_td < minCityTile) {
          minCityTile = city_td;
        }
      }
      // adding the tileanddir to city representants if doesn't exist
      addIfNotExist(localCityReps, minCityTile)
    }
  }
}

void GameCarcassonne::endGameCalculations() {
  struct meepleInfoPlus {
    meepleInfo meeple;
    vector<tileAndDir> cities;
  };

  // we need to collect all meeples left on the board at the end of the game.
  // we will do a classic breadth-first search on the board, starting at (0,0)

  queue<tileAndDir> q;   // queue for the bfs
  vector<tileAndDir> v;  // vector to mark as visited for the bfs

  // contains the smallest tileAndDir for each relevant completed city
  vector<tileAndDir> cityReps;
  vector<meepleInfoPlus> fieldMeeples;

  tileAndDir start = tileAndDir(0, 0, 0);
  q.push(start);
  v.push_back(start);

  tileAndDir curr = tileAndDir(0, 0, 0);
  tileAndDir neighbor = tileAndDir(0, 0, 0);

  while (!q.empty()) {
    curr = q.front();
    q.pop();  // pop() does not return anything, hence the use of front()

    // left neighbor :
    BFS_NEIGHBOR(curr.x - 1, curr.y)

    // top neighbor :
    BFS_NEIGHBOR(curr.x, curr.y - 1)

    // right neighbor :
    BFS_NEIGHBOR(curr.x + 1, curr.y)

    // bottom neighbor :
    BFS_NEIGHBOR(curr.x, curr.y + 1)

    TileCarcassonne* tile = (TileCarcassonne*) board.get(curr.x, curr.y);
    int meepdir = tile->getMeepleLocation();
    if (meepdir != -1) {
      meepleInfo meep{curr.x, curr.y, meepdir, tile->getMeeplePlayer()};
      // case road, city or monastery
      if ((meepdir == 13) ||
          ((meepdir == 0 || meepdir == 3 || meepdir == 6 || meepdir == 9) &&
           tile->getBorder(dirToBorder(meepdir)) != 'g')) {
        calculateEndScoresFromMeeple(meep);
      }
      // case grassland
      else {
        vector<tileAndDir> fieldVisited = vector<tileAndDir>();
        queue<meepleInfo> fieldMeepInfos = queue<meepleInfo>();

        searchGraph(
            tileAndDir{curr.x, curr.y, (uint8_t) meepdir},
            fieldVisited,
            nullptr,
            nullptr,
            &fieldMeepInfos,
            STOPCOND_NONE);

        vector<tileAndDir> localCityReps;

        for (tileAndDir x : fieldVisited) {
          addToLocalCompletedCities(localCityReps, x, 0);
          addToLocalCompletedCities(localCityReps, x, 1);
          addToLocalCompletedCities(localCityReps, x, 2);
          addToLocalCompletedCities(localCityReps, x, 3);
        }

        for (tileAndDir x : localCityReps) {
          addIfNotExist(cityReps, x)
        }

        while (!fieldMeepInfos.empty()) {
          meepleInfo meep = fieldMeepInfos.front();
          fieldMeeples.push_back({meep, localCityReps});
          // removing from model
          ((TileCarcassonne*) board.get(meep.x, meep.y))->removeMeeple();
          fieldMeepInfos.pop();
        }
      }
    }
  }

  int* meeplePerPlayer = new int[players.size()];

  for (tileAndDir rep : cityReps) {
    // reinitializing meeplePerPlayer
    for (size_t i = 0; i < players.size(); i++) {
      meeplePerPlayer[i] = 0;
    }

    // counting meeple per player in fields surrounding city
    for (meepleInfoPlus info : fieldMeeples) {
      for (tileAndDir localRep : info.cities) {
        if (rep == localRep) {
          meeplePerPlayer[info.meeple.player]++;
          break;
        }
      }
    }

    // counting max number of neighboring meeples
    int max = 0;
    for (uint j = 0; j < players.size(); j++) {
      if (max < meeplePerPlayer[j]) {
        max = meeplePerPlayer[j];
      }
    }

    // giving points to deserving players
    if (max > 0) {
      for (uint j = 0; j < players.size(); j++) {
        if (meeplePerPlayer[j] == max) {
          players.at(j)->addScore(4);
        }
      }
    }
  }

  delete[] meeplePerPlayer;
}

bool GameCarcassonne::canPlaceMeeple() {
  return currentPlayerHasPlacedTile && meepleVector[currentPlayer] > 0;
}

void GameCarcassonne::nextTurn() {
  if (bag.empty()) {
    gameIsOver = true;
    endGameCalculations();
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

int GameCarcassonne::getPlayerMeepleCount(int player) {
  return meepleVector[player];
}

void GameCarcassonne::discardTile() {
  nbOfDiscardedTiles++;
  nextTurn();
}

// ===================================================== //
// --- definition of functions for struct tileAndDir --- //
// ===================================================== //

GameCarcassonne::tileAndDir::tileAndDir(int _x, int _y, uint8_t _d) :
    x{_x},
    y{_y},
    d{_d} {}

bool GameCarcassonne::tileAndDir::operator==(tileAndDir b) const {
  return (b.x == x && b.y == y && b.d == d);
}

// arbitrary comparaison relation, useful for ordering elements
bool operator<(GameCarcassonne::tileAndDir b1, GameCarcassonne::tileAndDir b2) {
  return (
      (b1.x < b2.x) || (b1.x == b2.x && b1.y < b2.y) ||
      (b1.x == b2.x && b1.y == b2.y && b1.d < b2.d));
}
