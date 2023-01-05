#include "view/gameview/GameViewCarcassonne.hpp"
#include "model/game/GameCarcassonne.hpp"
#include "view/drawobject/DrawCarcassonne.hpp"
#include "view/drawobject/DrawMeeple.hpp"

using namespace std;
using namespace sf;

#define OFFSET_LONG 70
#define OFFSET_SHORT 40
#define MAX_MEEPLE_DIST 50

#define LOG(x) std::cout << x << std::endl

static const char* textControls =
    "Controls:\n"
    "Left click: place tile or meeple\n"
    "Right click: move camera\n"
    "Scroll: zoom\n"
    "A and Z: rotate\n"
    "Space: skip turn\n"
    "ESC: back to menu\n"
    "C: hide controls";

static const vec2f meepleOffset[14] = {

    {0, -OFFSET_LONG},
    {OFFSET_SHORT, -OFFSET_LONG},
    {OFFSET_LONG, -OFFSET_SHORT},
    {OFFSET_LONG, 0},
    {OFFSET_LONG, OFFSET_SHORT},
    {OFFSET_SHORT, OFFSET_LONG},
    {0, OFFSET_LONG},
    {-OFFSET_SHORT, OFFSET_LONG},
    {-OFFSET_LONG, OFFSET_SHORT},
    {-OFFSET_LONG, 0},
    {-OFFSET_LONG, -OFFSET_SHORT},
    {-OFFSET_SHORT, -OFFSET_LONG},
    {0, 0},
    {0, 0}};

GameViewCarcassonne::GameViewCarcassonne(Win* _win, int nbOfPlayers) :
    GameView(_win, new GameCarcassonne(nbOfPlayers), nullptr, textControls),
    // we grab the last tile, which is predefined
    curModelTile{(TileCarcassonne*) ((GameCarcassonne*) game)->grabTile()},
    skipTurn{false},
    scoreText{new DrawText(getAllPlayerInfo(), Color::White)},
    meepleList{list<MeepleData>()},
    lastPlacedTile{nullptr},
    potentialMeeple{new DrawMeeple(-1)},
    lastTileHasMonastery{false} {
  // the first tile is defined and placed in model and view
  ((GameCarcassonne*) game)->placeFirstTile(curModelTile);
  addTile(new DrawCarcassonne(curModelTile->getType()), 0, 0, 0);

  // we grab the new tile
  grabNextTile();

  // initializing text
  textList.push_back(scoreText);
  scoreText->setPosition(
      scoreText->getWidth() / 2 + 15, scoreText->getHeight() / 2 + 80);
  controlsText->move(0, scoreText->getHeight() + 30);
  ctrlTextPosition.y += scoreText->getHeight() + 30;

  firstPlay = false;  // only useful for the other games

  potentialMeeple->setParent(&cameraObject);
  potentialMeeple->setPosition(-1000000, -1000000);
}

GameViewCarcassonne::~GameViewCarcassonne() {
  if (curModelTile != nullptr) {
    delete curModelTile;
  }
  for (MeepleData meep : meepleList) {
    delete meep.meeple;
  }
  delete potentialMeeple;
}

void GameViewCarcassonne::grabNextTile() {
  curModelTile = (TileCarcassonne*) ((GameCarcassonne*) game)->grabTile();
  curTile = new DrawCarcassonne(curModelTile->getType());
  curTile->setParent(&cameraObject);
  lastTileHasMonastery = curModelTile->hasMonastery();
}

int GameViewCarcassonne::onKeyPress(Event& event) {
  switch (event.key.code) {
    case Keyboard::Space: {
      skipTurn = true;
      break;
    }
    default: { break; }
  }
  return 0;
}

void GameViewCarcassonne::tryToPlaceMeeple(int dir) {
  if (dir == 12) {
    dir = 13;
  }
  int res = ((GameCarcassonne*) game)->placeMeeple(dir);
  // if successful, adds meeple to view
  if (res != -1) {
    destRot = 0;
    curRot = 0;
    modelRot = 0;
    leftRotPress = false;
    rightRotPress = false;
    // yeeting potentialMeeple out of view
    potentialMeeple->setPosition(-1000000000.0f, -1000000000.0f);
    if (dir == -1) {
      delete curTile;
    } else {
      // adding meeple to view
      DrawMeeple* meep = (DrawMeeple*) curTile;
      meep->setParent(&cameraObject);
      meep->setPosition(lastPlacedTile->getPosition() + meepleOffset[res]);
      meep->setRotation(0);
      meepleList.push_back(
          {meep, {lastPlacedTilePos.x, lastPlacedTilePos.y, res}});
    }
    if (!game->isOver()) {
      // draw newt tile
      grabNextTile();
    } else {
      curTile = nullptr;
      curModelTile = nullptr;
    }
    scoreText->setText(getAllPlayerInfo());
  }
}

int GameViewCarcassonne::calculateMeepleDirection() {
  float scale = cameraObject.getSize().x;
  vec2f pos = lastPlacedTile->getPositionOnScreen();
  int dir = 0;
  float min_dist = 1.0e+30f;  // big number
  int maxVal = lastTileHasMonastery ? 13 : 12;

  for (int i = 0; i < maxVal; i++) {
    float x = mousePos.x - (pos.x + (meepleOffset[i].x) * scale);
    float y = mousePos.y - (pos.y + (meepleOffset[i].y) * scale);
    float dist = x * x + y * y;
    // no need to calculate sqrt because we only compare the distances
    if (dist < min_dist) {
      min_dist = dist;
      dir = i;
    }
  }
  float max_dist = MAX_MEEPLE_DIST * scale;
  if (min_dist > max_dist * max_dist) {
    dir = -1;
  }
  return dir;
}

void GameViewCarcassonne::changeState() {
  if (leftRotPress) {
    if (!((GameCarcassonne*) game)->canPlaceMeeple()) {
      curModelTile->rotateCounterClockwise();
    } else {
      destRot = -360;
      leftRotPress = false;
    }
  }

  if (rightRotPress) {
    if (!((GameCarcassonne*) game)->canPlaceMeeple()) {
      curModelTile->rotateClockwise();
    } else {
      destRot = 360;
      rightRotPress = false;
    }
  }

  if (skipTurn) {
    if (!game->isOver()) {
      if (((GameCarcassonne*) game)->canPlaceMeeple()) {
        tryToPlaceMeeple(-1);
      } else {
        destRot = 0;
        curRot = 0;
        modelRot = 0;
        leftRotPress = false;
        rightRotPress = false;
        ((GameCarcassonne*) game)->nextTurn();
        delete curTile;
        delete curModelTile;
        if (!game->isOver()) {
          grabNextTile();
        } else {
          curTile = nullptr;
          curModelTile = nullptr;
        }
      }
    }
    skipTurn = false;
  }

  int dir = -1;
  if (((GameCarcassonne*) game)->canPlaceMeeple()) {
    dir = calculateMeepleDirection();
    if (dir == -1) {
      potentialMeeple->setPosition(-1000000000.0f, -1000000000.0f);
    } else {
      potentialMeeple->setPosition(
          lastPlacedTile->getPosition() + meepleOffset[dir]);
    }
  }

  // ---- placing tile or meeple ---- //
  if (validM1Press) {
    if (!game->isOver()) {
      // case 1: placing a meeple
      if (((GameCarcassonne*) game)->canPlaceMeeple()) {
        dir = calculateMeepleDirection();
        if (dir != -1) {
          tryToPlaceMeeple(dir);
        }
      }
      // case 2: placing a tile
      else {
        // try to put tile in model
        vec2i aPos = coordToGridPos(mousePos);
        bool b = game->placeTile(curModelTile, aPos.x, aPos.y);

        // if successful, add tile to view
        if (b) {
          destRot = 0;
          curRot = 0;
          leftRotPress = false;
          rightRotPress = false;
          addTile(curTile, aPos.x, aPos.y, modelRot * 90);
          lastPlacedTile = curTile;
          lastPlacedTilePos = aPos;
          modelRot = 0;
          if (!game->isOver()) {
            // grabbing a meeple
            if (((GameCarcassonne*) game)->canPlaceMeeple()) {
              curModelTile = nullptr;
              curTile = new DrawMeeple(game->getCurrentPlayerIndex());
              curTile->setParent(&cameraObject);
              potentialMeeple->setPosition(-1000000000.0f, -1000000000.0f);
            }
            // grabbing a tile from bag
            else {
              grabNextTile();
            }
          } else {
            curTile = nullptr;
            curModelTile = nullptr;
          }
          scoreText->setText(getAllPlayerInfo());
        }
      }
    }
    validM1Press = false;
  }

  // removes the meeples that had been removed in model (once per frame)
  int meepleInfos[3];
  if (((GameCarcassonne*) game)->getLastRemovedMeepleInfo(meepleInfos)) {
    for (list<GameViewCarcassonne::MeepleData>::iterator it = begin(meepleList);
         it != end(meepleList);
         it++) {
      if (it->info[0] == meepleInfos[0] && it->info[1] == meepleInfos[1] &&
          it->info[2] == meepleInfos[2]) {
        delete it->meeple;
        meepleList.erase(it);
        break;
      }
    }
  }

  GameView::changeState();
}

string GameViewCarcassonne::getAllPlayerInfo() const {
  string s = "player:  meeples:  score:\n";
  std::vector<Player*> ps = game->getPlayers();
  int len = ps.size();

  for (int i = 0; i < len; i++) {
    string name = ps.at(i)->getName();
    string meeplecount =
        to_string(((GameCarcassonne*) game)->getPlayerMeepleCount(i));
    string score = to_string(ps.at(i)->getScore());

    name.resize(8, ' ');
    meeplecount.resize(9, ' ');
    score.resize(3, ' ');

    s += name + " " + meeplecount + " " + score;
    if (i != len - 1) {
      s += '\n';
    }
  }
  return s;
}

void GameViewCarcassonne::drawTiles() {
  GameView::drawTiles();
  potentialMeeple->draw(win);
  for (MeepleData meep : meepleList) {
    meep.meeple->draw(win);
  }
}
