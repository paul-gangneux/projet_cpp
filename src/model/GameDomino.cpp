#include "model/GameDomino.hpp"

GameDomino::GameDomino() :
  Game(),
  bag{std::vector<TileDomino*>()}
{
  for (size_t i=0; i < 10 * (getPlayers()).size(); i++){
    bag.push_back(new TileDomino());
  }
}

GameDomino::~GameDomino(){
  while (!bag.empty()){
    delete bag.back();
  }
}

void GameDomino::gameOver(){}

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

bool GameDomino::placeTile(int x, int y, Tile * const _tile){
  if (Game::placeTile(x,y,_tile)) {
    
  }
}
