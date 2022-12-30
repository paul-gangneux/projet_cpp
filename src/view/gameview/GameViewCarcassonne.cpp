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
    "Space: next turn (don't place a meeple)\n"
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

GameViewCarcassonne::GameViewCarcassonne(Win* _win) :
    GameView(_win, new GameCarcassonne(), nullptr, textControls),
    // we grab the last tile, which is predefined
    curModelTile{(TileCarcassonne*) ((GameCarcassonne*) game)->grabTile()},
    skipTurn{false},
    scoreText{new DrawText(getScores(), Color::White)},
    meepleList{list<DrawMeeple*>()},
    lastPlacedTile{nullptr},
    potentialMeeple{new DrawMeeple(-1)} {
  // the first tile is defined and placed in model and view
  ((GameCarcassonne*) game)->placeFirstTile(curModelTile);
  addTile(new DrawCarcassonne(curModelTile->getType()), 0, 0, 0);

  // we grab the new tile
  curModelTile = (TileCarcassonne*) ((GameCarcassonne*) game)->grabTile();
  curTile = new DrawCarcassonne(curModelTile->getType());
  curTile->setParent(&cameraObject);

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
  for (DrawMeeple* meep : meepleList) {
    delete meep;
  }
  delete potentialMeeple;
}

int GameViewCarcassonne::onKeyPress(Event& event) {
  switch (event.key.code) {
    case Keyboard::Space: {
      if (!game->isOver()) {
        tryToPlaceMeeple(-1);
        break;
      }
    }
    default: { break; }
  }
  return 0;
}

void GameViewCarcassonne::tryToPlaceMeeple(int dir) {
  if (dir == 12) {
    dir = 13;
  }
  bool b = ((GameCarcassonne*) game)->placeMeeple(dir);
  // if successful, adds meeple to view
  if (b) {
    destRot = 0;
    curRot = 0;
    modelRot = 0;
    // removing potentialMeeple
    potentialMeeple->setPosition(-1000000000.0f, -1000000000.0f);
    if (dir == -1) {
      delete curTile;
    } else {
      // adding meeple to view
      DrawMeeple* meep = (DrawMeeple*) curTile;
      meep->setParent(&cameraObject);
      meep->setPosition(lastPlacedTile->getPosition() + meepleOffset[dir]);
      meep->setRotation(0);
      meepleList.push_back(meep);
      // todo, store data about meeple somewhere
    }
    if (!game->isOver()) {
      // draw newt tile
      curModelTile = (TileCarcassonne*) ((GameCarcassonne*) game)->grabTile();
      curTile = new DrawCarcassonne(curModelTile->getType());
      curTile->setParent(&cameraObject);
    } else {
      curTile = nullptr;
      curModelTile = nullptr;
    }
    scoreText->setText(getScores());
  }
}

int GameViewCarcassonne::calculateMeepleDirection() {
  float scale = cameraObject.getSize().x;
  vec2f pos = lastPlacedTile->getPositionOnScreen();
  int dir = 0;
  float min_dist = 999999999999.0f;

  for (int i = 0; i < 13; i++) {
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

  if (validM1Press) {
    if (!game->isOver()) {
      // case 1: placing a meeple
      if (((GameCarcassonne*) game)->canPlaceMeeple()) {
        dir = calculateMeepleDirection();
        if (dir != -1)
          tryToPlaceMeeple(dir);
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
          addTile(curTile, aPos.x, aPos.y, modelRot * 90);
          lastPlacedTile = curTile;
          modelRot = 0;
          if (!game->isOver()) {
            // drawing a meeple
            if (((GameCarcassonne*) game)->canPlaceMeeple()) {
              curModelTile = nullptr;
              curTile = new DrawMeeple(game->getCurrentPlayerIndex());
              curTile->setParent(&cameraObject);
              potentialMeeple->setPosition(-1000000000.0f, -1000000000.0f);
            }
            // drawing a tile
            else {
              curModelTile =
                  (TileCarcassonne*) ((GameCarcassonne*) game)->grabTile();
              curTile = new DrawCarcassonne(curModelTile->getType());
              curTile->setParent(&cameraObject);
            }
          } else {
            curTile = nullptr;
            curModelTile = nullptr;
          }
          scoreText->setText(getScores());
        }
      }
    }
    validM1Press = false;
  }

  if (skipTurn) {
    destRot = 0;
    curRot = 0;
    modelRot = 0;
    ((GameCarcassonne*) game)->nextTurn();
    if (!game->isOver()) {
      curModelTile = (TileCarcassonne*) ((GameCarcassonne*) game)->grabTile();
      curTile = new DrawCarcassonne(curModelTile->getType());
      curTile->setParent(&cameraObject);
    } else {
      curTile = nullptr;
    }
    skipTurn = false;
  }

  GameView::changeState();
}

void GameViewCarcassonne::drawTiles() {
  GameView::drawTiles();
  potentialMeeple->draw(win);
  for (DrawMeeple* meep : meepleList) {
    meep->draw(win);
  }
}
