#include "model/game/GameTrax.hpp"

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

GameTrax::GameTrax() : Game(), gameIsOver{false}, nbOfTiles{0} {}

GameTrax::~GameTrax() {
  while (!placedTilesQueue.empty()) {
    int* i = placedTilesQueue.front();
    placedTilesQueue.pop();
    delete[] i;
  }
}

bool GameTrax::isOver() {
  return gameIsOver;
}

bool GameTrax::canAddNewPlayer() {
  return true;
}

char GameTrax::getColorIfExists(int x, int y, int colorPos) {
  char c;
  TileTrax* t = (TileTrax*)board.get(x, y);
  if (t != nullptr) {
    c = t->getColor(colorPos);
  } else {
    c = '\0';
  }
  return c;
}

void GameTrax::playIfForced(int x, int y) {
  if (nbOfTiles >= 64)
    return;

  TileTrax* t = (TileTrax*)board.get(x, y);
  if (t != nullptr)
    return;

  char up = getColorIfExists(x, y - 1, 2);
  char right = getColorIfExists(x + 1, y, 3);
  char down = getColorIfExists(x, y + 1, 0);
  char left = getColorIfExists(x - 1, y, 1);

  // case straight tile
  if (up == down && up != '\0') {
    if (up == 'b') {
      placeTile(new TileTrax(0, 0), x, y);
    } else {
      placeTile(new TileTrax(0, 1), x, y);
    }
  } else if (left == right && left != '\0') {
    if (left == 'w') {
      placeTile(new TileTrax(0, 0), x, y);
    } else {
      placeTile(new TileTrax(0, 1), x, y);
    }
  }
  // case curved tile

  else if (up == right && up != '\0') {
    if (up == 'w') {
      placeTile(new TileTrax(1, 0), x, y);
    } else {
      placeTile(new TileTrax(1, 2), x, y);
    }
  } else if (right == down && right != '\0') {
    if (right == 'w') {
      placeTile(new TileTrax(1, 1), x, y);
    } else {
      placeTile(new TileTrax(1, 3), x, y);
    }
  } else if (down == left && down != '\0') {
    if (down == 'w') {
      placeTile(new TileTrax(1, 2), x, y);
    } else {
      placeTile(new TileTrax(1, 0), x, y);
    }
  } else if (left == up && left != '\0') {
    if (left == 'w') {
      placeTile(new TileTrax(1, 3), x, y);
    } else {
      placeTile(new TileTrax(1, 1), x, y);
    }
  }
}

bool GameTrax::checkPathForLoop(
    int origX, int origY, char col, int x, int y, int dir) {
  if (x == origX && y == origY)
    return true;

  int colors[4] = {getColorIfExists(x, y, 0),
                   getColorIfExists(x, y, 1),
                   getColorIfExists(x, y, 2),
                   getColorIfExists(x, y, 3)};

  colors[dir] = '\0';
  if (colors[0] == col) {
    return checkPathForLoop(origX, origY, col, x, y - 1, 2);
  } else if (colors[1] == col) {
    return checkPathForLoop(origX, origY, col, x + 1, y, 3);
  } else if (colors[2] == col) {
    return checkPathForLoop(origX, origY, col, x, y + 1, 0);
  } else if (colors[3] == col) {
    return checkPathForLoop(origX, origY, col, x - 1, y, 1);
  }
  return false;
}

// changes value of gameIsOver, and winners, if game is finished
void GameTrax::checkForEndGame(int x, int y) {
  if (nbOfTiles >= 64)
    gameIsOver = true;

  bool win1, win2;

  char col1 = getColorIfExists(x, y, 0);
  char col2 = getColorIfExists(x, y, 1);

  win1 = checkPathForLoop(x, y, col1, x, y - 1, 2);
  if (col1 != col2) {
    win2 = checkPathForLoop(x, y, col2, x + 1, y, 3);
  } else {
    col2 = getColorIfExists(x, y, 2);
    win2 = checkPathForLoop(x, y, col2, x, y + 1, 0);
  }

  // TODO: check for length of 8

  // TODO: state who won in a variable
  if (win1 || win2)
    gameIsOver = true;
}

bool GameTrax::placeTile(Tile* const tile, int x, int y) {
  bool res = Game::placeTile(tile, x, y);
  if (res) {
    nbOfTiles++;
    placedTilesQueue.push(new int[4]{
        ((TileTrax*)tile)->getType(), x, y, ((TileTrax*)tile)->getRotation()});
    checkForEndGame(x, y);
    playIfForced(x + 1, y);
    playIfForced(x - 1, y);
    playIfForced(x, y + 1);
    playIfForced(x, y - 1);
  }
  return res;
};

// bool GameTrax::placeTile(int tyleType, int rotation, int x, int y) {
//   //todo ?
// };

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
