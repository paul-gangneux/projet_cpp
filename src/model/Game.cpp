#include "model/Game.hpp"

Player* players;
Board board;
std::vector<Tile*> bag;

Tile* grabTile(){
  if (bag.empty()) return nullptr;
  Tile* res = bag.back();
  bag.pop_back(); // no, pop_back does not return anything
  return res;
}