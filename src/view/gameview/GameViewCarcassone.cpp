#include "view/gameview/GameViewCarcassone.hpp"
// #include "model/game/GameCarcassone.hpp"
#include "view/drawobject/DrawCarcassone.hpp"

using namespace std;
using namespace sf;

static const char* textControls =
    "Controls:\n"
    "Left click: place tile or meeple\n"
    "Right click: move camera\n"
    "Scroll: zoom\n"
    "A and Z: rotate\n"
    "Space: next turn (don't place a meeple)\n"
    "ESC: back to menu\n"
    "C: hide controls";

GameViewCarcassone::GameViewCarcassone(Win* _win) :
    GameView(_win, /* new GameCarcassone() */ nullptr, nullptr, textControls),
    // curModelTile{(TileCarcassone*) ((GameCarcassone*) game)->grabTile()},
    skipTurn{false},
    scoreText{new DrawText(getScores(), Color::White)} {
  curTile = new DrawCarcassone(1);  // todo : get type
  curTile->setParent(&cameraObject);
  textList.push_back(scoreText);
  scoreText->setPosition(
      scoreText->getWidth() / 2 + 15, scoreText->getHeight() / 2 + 80);
  controlsText->move(0, scoreText->getHeight() + 30);
  ctrlTextPosition.y += scoreText->getHeight() + 30;
}

GameViewCarcassone::~GameViewCarcassone() {}

int GameViewCarcassone::onKeyPress(Event& event) {
  switch (event.key.code) {
    case Keyboard::Space: {
      if (!game->isOver()) {
        // todo: next turn without placing meeple
        break;
      }
    }
    default: { break; }
  }
  return 0;
}

void GameViewCarcassone::changeState() {
  if (leftRotPress) {
    // curModelTile->rotateCounterClockwise();
  }

  if (rightRotPress) {
    // curModelTile->rotateClockwise();
  }

  if (validM1Press) {
    if (!game->isOver()) {
      // sets position to 0,0 if it's the first play
      // or maybe it's useless since we're supposed to
      // already have a tile when we start
      vec2i aPos;
      if (firstPlay) {
        aPos = vec2i(0, 0);
        firstPlay = false;
      } else {
        aPos = coordToGridPos(mousePos);
      }

      // try to put tile in model
      // bool b = game->placeTile(curModelTile, aPos.x, aPos.y);
      bool b = false;

      // if successful, add tile to view
      if (b) {
        destRot = 0;
        curRot = 0;
        // addTile(curTile, aPos.x, aPos.y, modelRot * 90);
        modelRot = 0;
        if (!game->isOver()) {
          // curModelTile = (TileCarcassone*) ((GameCarcassone*)
          // game)->grabTile(); curTile = new DrawCarcassone(curModelTile);
          // curTile->setParent(&cameraObject);
        } else {
          curTile = nullptr;
        }
        scoreText->setText(getScores());
      }
    }
    validM1Press = false;
  }

  if (skipTurn) {
    destRot = 0;
    curRot = 0;
    modelRot = 0;
    // ((GameCarcassone*) game)->nextTurn();
    if (!game->isOver()) {
      // curModelTile = (TileCarcassone*) ((GameCarcassone*) game)->grabTile();
      // curTile = new DrawCarcassone(curModelTile->getType());
      // curTile->setParent(&cameraObject);
    } else {
      curTile = nullptr;
    }
    skipTurn = false;
  }

  GameView::changeState();
}
