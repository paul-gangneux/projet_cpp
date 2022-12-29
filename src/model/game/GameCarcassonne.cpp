#include "model/game/GameCarcassonne.hpp"
#include "model/tile/TileCarcassonne.hpp"

#include <algorithm>
#include <iostream>

#define putInBag(type, num)                   \
  for (size_t i = 0; i < num; i++) {          \
    bag.push_back(new TileCarcassonne(type)); \
  }

GameCarcassonne::GameCarcassonne() :
    Game(),
    bag{std::vector<TileCarcassonne*>()},
    currentPlayerHasPlacedTile{false} {
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
    return true;
  }
  return false;
}

bool GameCarcassonne::placeMeeple(int _dir) {
  if (!currentPlayerHasPlacedTile)
    return false;
  // TODO
  nextTurn();
  return true;
}

void GameCarcassonne::nextTurn() {
  Game::nextTurn();
  currentPlayerHasPlacedTile = false;
}
