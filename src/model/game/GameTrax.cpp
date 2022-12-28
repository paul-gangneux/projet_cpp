#include "model/game/GameTrax.hpp"

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

GameTrax::GameTrax() :
    Game("white", "black"),
    nbOfTiles{0},
    minX{0},
    maxX{0},
    minY{0},
    maxY{0} {}

GameTrax::~GameTrax() {
  while (!placedTilesQueue.empty()) {
    int* i = placedTilesQueue.front();
    placedTilesQueue.pop();
    delete[] i;
  }
}

bool GameTrax::canAddNewPlayer() {
  return false;
}

char GameTrax::getColorIfExists(int x, int y, int colorPos) {
  char c;
  TileTrax* t = (TileTrax*) board.get(x, y);
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

  TileTrax* t = (TileTrax*) board.get(x, y);
  if (t != nullptr)
    return;

  char up = getColorIfExists(x, y - 1, 2);
  char right = getColorIfExists(x + 1, y, 3);
  char down = getColorIfExists(x, y + 1, 0);
  char left = getColorIfExists(x - 1, y, 1);

  // case straight tile
  if (up == down && up != '\0') {
    if (up == 'b') {
      placeTileAux(new TileTrax(0, 0), x, y);
    } else {
      placeTileAux(new TileTrax(0, 1), x, y);
    }
  } else if (left == right && left != '\0') {
    if (left == 'w') {
      placeTileAux(new TileTrax(0, 0), x, y);
    } else {
      placeTileAux(new TileTrax(0, 1), x, y);
    }
  }
  // case curved tile

  else if (up == right && up != '\0') {
    if (up == 'w') {
      placeTileAux(new TileTrax(1, 0), x, y);
    } else {
      placeTileAux(new TileTrax(1, 2), x, y);
    }
  } else if (right == down && right != '\0') {
    if (right == 'w') {
      placeTileAux(new TileTrax(1, 1), x, y);
    } else {
      placeTileAux(new TileTrax(1, 3), x, y);
    }
  } else if (down == left && down != '\0') {
    if (down == 'w') {
      placeTileAux(new TileTrax(1, 2), x, y);
    } else {
      placeTileAux(new TileTrax(1, 0), x, y);
    }
  } else if (left == up && left != '\0') {
    if (left == 'w') {
      placeTileAux(new TileTrax(1, 3), x, y);
    } else {
      placeTileAux(new TileTrax(1, 1), x, y);
    }
  }
}

bool GameTrax::checkPath(
    vec2i pos, vec2i ori, bool xtrm[4], char col, int dir) {
  TileTrax* t = (TileTrax*) board.get(pos.x, pos.y);
  if (t == nullptr)
    return false;

  xtrm[0] = xtrm[0] || ((pos.x == minX) && (t->getColor(3) == col));
  xtrm[1] = xtrm[1] || ((pos.x == maxX) && (t->getColor(1) == col));
  xtrm[2] = xtrm[2] || ((pos.y == minY) && (t->getColor(0) == col));
  xtrm[3] = xtrm[3] || ((pos.y == maxY) && (t->getColor(2) == col));

  if (pos == ori)
    return true;

  int colors[4] = {
      t->getColor(0), t->getColor(1), t->getColor(2), t->getColor(3)};
  colors[dir] = '\0';

  if (colors[0] == col) {
    return checkPath(vec2i{pos.x, pos.y - 1}, ori, xtrm, col, 2);
  } else if (colors[1] == col) {
    return checkPath(vec2i{pos.x + 1, pos.y}, ori, xtrm, col, 3);
  } else if (colors[2] == col) {
    return checkPath(vec2i{pos.x, pos.y + 1}, ori, xtrm, col, 0);
  } else if (colors[3] == col) {
    return checkPath(vec2i{pos.x - 1, pos.y}, ori, xtrm, col, 1);
  }
  return false;
}

// changes value of gameIsOver, and winners, if game is finished
void GameTrax::checkForEndGame(int x, int y) {
  if (nbOfTiles >= 64)
    gameIsOver = true;

  char col_up = getColorIfExists(x, y, 0);  // up
  char col_ri = getColorIfExists(x, y, 1);  // right
  char col_do = getColorIfExists(x, y, 2);  // down
  char col_le = getColorIfExists(x, y, 3);  // left

  bool xtrm_w[4]{false, false, false, false};
  bool xtrm_b[4]{false, false, false, false};

  xtrm_w[0] = ((x == minX) && (col_le == 'w'));
  xtrm_w[1] = ((x == maxX) && (col_ri == 'w'));
  xtrm_w[2] = ((y == minY) && (col_up == 'w'));
  xtrm_w[3] = ((y == maxY) && (col_do == 'w'));

  xtrm_b[0] = ((x == minX) && (col_le == 'b'));
  xtrm_b[1] = ((x == maxX) && (col_ri == 'b'));
  xtrm_b[2] = ((y == minY) && (col_up == 'b'));
  xtrm_b[3] = ((y == maxY) && (col_do == 'b'));

  bool loop_w = false;
  bool loop_b = false;

  if (col_up == 'w') {  // up
    loop_w = checkPath(vec2i{x, y - 1}, vec2i{x, y}, xtrm_w, 'w', 2);
  } else {
    loop_b = checkPath(vec2i{x, y - 1}, vec2i{x, y}, xtrm_b, 'b', 2);
  }
  if (col_ri == 'w') {  // right
    loop_w = checkPath(vec2i{x + 1, y}, vec2i{x, y}, xtrm_w, 'w', 3);
  } else {
    loop_b = checkPath(vec2i{x + 1, y}, vec2i{x, y}, xtrm_b, 'b', 3);
  }
  if (col_do == 'w') {  // down
    loop_w = checkPath(vec2i{x, y + 1}, vec2i{x, y}, xtrm_w, 'w', 0);
  } else {
    loop_b = checkPath(vec2i{x, y + 1}, vec2i{x, y}, xtrm_b, 'b', 0);
  }
  if (col_le == 'w') {  // left
    loop_w = checkPath(vec2i{x - 1, y}, vec2i{x, y}, xtrm_w, 'w', 1);
  } else {
    loop_b = checkPath(vec2i{x - 1, y}, vec2i{x, y}, xtrm_b, 'b', 1);
  }

  int ampl_x = maxX - minX;
  int ampl_y = maxY - minY;

  bool win_w = loop_w || (ampl_x >= 7 && xtrm_w[0] && xtrm_w[1]) ||
               (ampl_y >= 7 && xtrm_w[2] && xtrm_w[3]);

  bool win_b = loop_b || (ampl_x >= 7 && xtrm_b[0] && xtrm_b[1]) ||
               (ampl_y >= 7 && xtrm_b[2] && xtrm_b[3]);

  if (win_w || win_b) {
    if (win_w && getPlayers().at(0)->getScore() == 0) {
      getPlayers().at(0)->addScore(1);
    }
    if (win_b && getPlayers().at(1)->getScore() == 0) {
      getPlayers().at(1)->addScore(1);
    }
    gameIsOver = true;
  }
}

bool GameTrax::placeTileAux(Tile* const tile, int x, int y) {
  bool res = (maxX - minX < 7 || (x >= minX && x <= maxX)) &&
             (maxY - minY < 7 || (y >= minY && y <= maxY)) &&
             Game::placeTile(tile, x, y);
  if (res) {
    nbOfTiles++;
    minX = MIN(minX, x);
    minY = MIN(minY, y);
    maxX = MAX(maxX, x);
    maxY = MAX(maxY, y);
    placedTilesQueue.push(new int[4]{((TileTrax*) tile)->getType(),
                                     x,
                                     y,
                                     ((TileTrax*) tile)->getRotation()});
    checkForEndGame(x, y);
    playIfForced(x + 1, y);
    playIfForced(x - 1, y);
    playIfForced(x, y + 1);
    playIfForced(x, y - 1);
  }
  return res;
}

bool GameTrax::placeTile(Tile* const tile, int x, int y) {
  bool res = placeTileAux(tile, x, y);
  if (res) {
    if (gameIsOver) {
      Player* w = getPlayers().at(0);
      Player* b = getPlayers().at(1);
      if (w->getScore() == 1 && b->getScore() == 1) {
        getPlayers().at(currentPlayer)->addScore(1);
      }
    } else {
      nextTurn();
    }
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
