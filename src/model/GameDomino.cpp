#include "model/GameDomino.hpp"

// [NOTE] if returns nullptr, end the game.
Tile* GameDomino::grabTile(){
  if (bag.empty()) {
    gameOver(); // not be the best way to do it. we end game then we come back to this function (pile) to return a nullptr ? eeeh
    return nullptr;
  }
  Tile* res = bag.back();
  bag.pop_back(); // no, pop_back does not return anything
  return res;
}