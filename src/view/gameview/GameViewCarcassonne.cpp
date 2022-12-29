#include "view/gameview/GameViewCarcassonne.hpp"
#include "model/game/GameCarcassonne.hpp"
#include "view/drawobject/DrawCarcassonne.hpp"

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

GameViewCarcassonne::GameViewCarcassonne(Win* _win) :
    GameView(_win, new GameCarcassonne(), nullptr, textControls),
    // we grab the last tile, which is predefined
    curModelTile{(TileCarcassonne*) ((GameCarcassonne*) game)->grabTile()},
    skipTurn{false},
    scoreText{new DrawText(getScores(), Color::White)} {
  // the first tile is defined and placed in model and view
  game->placeTile(curModelTile, 0, 0);
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
}

GameViewCarcassonne::~GameViewCarcassonne() {}

int GameViewCarcassonne::onKeyPress(Event& event) {
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

void GameViewCarcassonne::changeState() {
  if (leftRotPress) {
    curModelTile->rotateCounterClockwise();
  }

  if (rightRotPress) {
    curModelTile->rotateClockwise();
  }

  if (validM1Press) {
    if (!game->isOver()) {
      // try to put tile in model
      vec2i aPos = coordToGridPos(mousePos);
      bool b = game->placeTile(curModelTile, aPos.x, aPos.y);

      // if successful, add tile to view
      if (b) {
        destRot = 0;
        curRot = 0;
        addTile(curTile, aPos.x, aPos.y, modelRot * 90);
        modelRot = 0;
        if (!game->isOver()) {
          curModelTile =
              (TileCarcassonne*) ((GameCarcassonne*) game)->grabTile();
          curTile = new DrawCarcassonne(curModelTile->getType());
          curTile->setParent(&cameraObject);
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
