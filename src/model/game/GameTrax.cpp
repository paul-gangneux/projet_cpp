#include "model/game/GameTrax.hpp"

GameTrax::GameTrax() :
  Game()
{
 
}

GameTrax::~GameTrax() {
  while (!placedTilesQueue.empty()) {
    int* i = placedTilesQueue.front();
    placedTilesQueue.pop();
    delete[] i;
  }
}

bool GameTrax::gameOver(){
  return false; //todo
}

bool GameTrax::canAddNewPlayer() {
  return true;
}

char GameTrax::getColorIfExists(int x, int y, int colorPos) {
  char c;
  TileTrax* t = (TileTrax*) board.get(x, y);
  if (t!= nullptr) {
    c = t->getColor(colorPos);
  } else {
    c = '\0';
  }
  return c;
}

void GameTrax::playIfForced(int x, int y) {
  TileTrax* t = (TileTrax*) board.get(x, y);
  if (t == nullptr) {
    char up = getColorIfExists(x, y - 1, 2);
    char right = getColorIfExists(x + 1, y, 3);
    char down = getColorIfExists(x, y + 1, 0);
    char left = getColorIfExists(x - 1, y, 1);

    // TODO
  }
}

bool GameTrax::placeTile(Tile* const tile, int x, int y) {
  bool res = Game::placeTile(tile, x, y);
  if (res) {
    // TODO: check for end of game
    placedTilesQueue.push(new int[4] {((TileTrax*) tile)->getType(), x, y, ((TileTrax*) tile)->getRotation()});
    playIfForced(x + 1, y);
    playIfForced(x - 1, y);
    playIfForced(x, y + 1);
    playIfForced(x, y - 1);
  }
  return res;
};

bool GameTrax::getTileInfoInPlaceQueue(int infos[4]) {
  if (placedTilesQueue.empty()) {
    return false;
  }
  int* i = placedTilesQueue.front();
  infos[0] = i[0];
  infos[1] = i[1];
  infos[2] = i[2];
  infos[3] = i[3];
  placedTilesQueue.pop();
  delete[] i;
  return true;
}
