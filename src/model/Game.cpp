#include "model/Game.hpp"

Tile* Game::grabTile() {
  if (bag.empty()) return nullptr;
  Tile* res = bag.back();
  bag.pop_back(); // no, pop_back does not return anything
  return res;
}