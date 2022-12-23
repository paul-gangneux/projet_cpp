#include "model/game/GameDomino.hpp"

#include <iostream>

GameDomino::GameDomino() : Game(), bag{std::vector<TileDomino*>()} {
  for (size_t i = 0; i < 10 * (getPlayers()).size(); i++) {
    bag.push_back(new TileDomino());
  }
}

GameDomino::~GameDomino() {}

bool GameDomino::canAddNewPlayer() {
  return true;  // always return true since we can have infinite players playing
                // a domino game
}

Tile* GameDomino::grabTile() {
  if (bag.empty()) {
    // --- DEBUG
    std::cout << std::endl
              << "OOPSIE: GameDomino::grabTile() was called, but the bag is "
                 "empty. Check value of isGameOver"
              << std::endl;
    std::exit(1);
    // --- end debug
  }
  Tile* res = bag.back();
  bag.pop_back();  // no, pop_back does not return anything
  return res;
}

bool GameDomino::placeTile(Tile* const _tile, int x, int y) {
  if (Game::placeTile(_tile, x, y)) {
    const TileDomino* local = dynamic_cast<const TileDomino*>(_tile);
    if (local == nullptr) {
      // --- DEBUG
      std::cout << std::endl
                << "OOPSIE: GameDomino::placeTile(...) did not cast correctly "
                   "a Tile to a TileDomino"
                << std::endl;
      // --- end debug
      std::exit(1);
    }
    int score = 0;
    const int* nums = local->getNumbers();

    if (board.get(x, y - 1) != nullptr)
      score += (nums[0] + nums[1] + nums[2]);
    if (board.get(x + 1, y) != nullptr)
      score += (nums[3] + nums[4] + nums[5]);
    if (board.get(x, y + 1) != nullptr)
      score += (nums[6] + nums[7] + nums[8]);
    if (board.get(x - 1, y) != nullptr)
      score += (nums[9] + nums[10] + nums[11]);

    (*players.at(currentPlayer)).addScore(score);

    // if the tile that has just been placed was the last one, game is over.
    if (bag.size() == 0)
      gameIsOver = true;

    nextTurn();
    return true;
  }
  return false;
}

void GameDomino::discardTile(Tile* _tile) {
  // since the tile will be removed from the bag & not placed on the board,
  // it won't ever serve again. we can delete it immediately and not risk a
  // double delete
  delete _tile;

  // if the tile that has just been discarded was the last one, game is over.
  if (bag.size() == 0)
    gameIsOver = true;

  nextTurn();
}