#include "model/game/GameDomino.hpp"

#include <iostream>

GameDomino::GameDomino() : Game(), bag{std::vector<TileDomino*>()} {
  for (size_t i = 0; i < 10 * (getPlayers()).size(); i++) {
    bag.push_back(new TileDomino());
  }
}

GameDomino::~GameDomino() {}

bool GameDomino::isOver() {
  return false;  // todo
}

bool GameDomino::canAddNewPlayer() {
  return true;  // always return true since we can have infinite gamers playing
                // a domino game
}

// [NOTE] if returns nullptr, end the game.
Tile* GameDomino::grabTile() {
  if (bag.empty()) {
    isOver();  // not be the best way to do it. we end game then we come back to
               // this function (pile) to return a nullptr ? eeeh
    return nullptr;
  }
  Tile* res = bag.back();
  bag.pop_back();  // no, pop_back does not return anything
  return res;
}

bool GameDomino::placeTile(Tile* const _tile, int x, int y) {
  if (Game::placeTile(_tile, x, y)) {
    const TileDomino* local = dynamic_cast<const TileDomino*>(_tile);
    if (local == nullptr) {
      std::cout << std::endl
                << "OOPSIE: GameDomino::placeTile(...) did not cast correctly "
                   "a Tile to a TileDomino"
                << std::endl;
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
    return true;
  }
  return false;
}