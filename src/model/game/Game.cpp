#include "model/game/Game.hpp"

#include <iostream>

Game::Game() :
    players{std::vector<Player*>()},
    board{Board()},
    currentPlayer{0},
    firstPlay{true},
    gameIsOver{false} {}

Game::~Game() {
  for (Player* p : players) {
    delete p;
  }
}

std::vector<Player*> const Game::getPlayers() const {
  return players;
}

bool Game::isOver() {
  return gameIsOver;
}

bool Game::canAddNewPlayer() {
  // --- DEBUG
  std::cout << std::endl
            << "OOPSIE: Game::canAddNewPlayer() should never be directly called"
            << std::endl;
  std::exit(1);
  // --- end debug
  return false;
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