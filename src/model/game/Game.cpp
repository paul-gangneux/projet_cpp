#include "model/game/Game.hpp"

#include <iostream>

Game::Game(const char* p1name, const char* p2name) :
    players{std::vector<Player*>()},
    board{Board()},
    currentPlayer{0},
    firstPlay{true},
    gameIsOver{false} {
  addPlayer(p1name);
  addPlayer(p2name);
}

Game::Game() : Game("player 1", "player 2") {}

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
  if (firstPlay) {
    board.placeTileForced(tile, x, y);
    firstPlay = false;
    return true;
  }
  return board.placeTile(tile, x, y);
}