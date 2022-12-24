#include "model/game/Game.hpp"

#include <iostream>

Game::Game() :
    players{std::vector<Player*>()},
    board{Board()},
    currentPlayer{0},
    firstPlay{true},
    gameIsOver{false} {
  addPlayer();
  addPlayer();
}

Game::~Game() {
  for (Player* p : players) {
    delete p;
  }
}

std::vector<Player*> const Game::getPlayers() const {
  return players;
}

Player const* Game::getCurrentPlayer() const {
  return players.at(currentPlayer);
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