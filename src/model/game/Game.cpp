#include "model/game/Game.hpp"
#include <iostream>

using namespace std;

// Game::Game() : Game("player 1", "player 2") {}

Game::Game(const char* p1name, const char* p2name, int nb_of_tiles) :
    Game::Game(2, nb_of_tiles) {
  players.at(0)->setName(p1name);
  players.at(1)->setName(p2name);
}

Game::Game(int nb_of_players, int nb_of_tiles) :
    players{std::vector<Player*>()},
    board{Board()},
    currentPlayer{0},
    firstPlay{true},
    gameIsOver{false},
    nbOfPlacedTiles{0},
    nbOfDiscardedTiles{0},
    maxNbOfTiles{nb_of_tiles} {
  if (nb_of_players < 2) {
    throw std::invalid_argument("player count can't be under 2");
  }
  for (int i = 1; i <= nb_of_players; i++) {
    if (!canAddNewPlayer()) {
      throw std::invalid_argument("player count too big");
    }
    addPlayer("player " + to_string(i));
  }
}

Game::~Game() {
  for (Player* p : players) {
    delete p;
  }
}

const std::vector<Player*>& Game::getPlayers() const {
  return players;
}

Player const* Game::getCurrentPlayer() const {
  return players.at(currentPlayer);
}

int Game::getCurrentPlayerIndex() const {
  return currentPlayer;
}

bool Game::isOver() {
  return gameIsOver;
}

bool Game::canAddNewPlayer() {
  return true;
}

bool Game::addPlayer() {
  if (!canAddNewPlayer())
    return false;

  Player* p = new Player(players.size() + 1);

  if (p == nullptr)
    return false;

  players.push_back(p);
  return true;
}

bool Game::addPlayer(const char* name) {
  return addPlayer(name);
}

bool Game::addPlayer(const string name) {
  if (!canAddNewPlayer())
    return false;

  Player* p = new Player(name);

  if (p == nullptr)
    return false;

  players.push_back(p);
  return true;
}

void Game::nextTurn() {
  currentPlayer = (currentPlayer + 1) % players.size();
}

bool Game::placeTile(Tile* const tile, int x, int y) {
  bool res;
  if (firstPlay) {
    board.placeTileForced(tile, x, y);
    firstPlay = false;
    res = true;
  } else {
    res = board.placeTile(tile, x, y);
  }
  if (res) {
    nbOfPlacedTiles++;
  }
  return res;
}

int Game::nbOfTilesLeft() {
  return maxNbOfTiles - nbOfPlacedTiles - nbOfDiscardedTiles;
}