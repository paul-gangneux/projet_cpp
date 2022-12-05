#include "model/GameDomino.hpp"

bool GameDomino::canAddNewPlayer() {
  return true; //always return true since we can have infinite gamers playing a domino game
}

// [NOTE] if returns nullptr, end the game.
Tile* GameDomino::grabTile() {
  if (bag.empty()) {
    gameOver(); // not be the best way to do it. we end game then we come back to this function (pile) to return a nullptr ? eeeh
    return nullptr;
  }
  Tile* res = bag.back();
  bag.pop_back(); // no, pop_back does not return anything
  return res;
}