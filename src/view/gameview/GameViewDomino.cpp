#include "view/gameview/GameViewDomino.hpp"
#include <iostream>
#include "model/game/GameDomino.hpp"
#include "view/drawobject/DrawDomino.hpp"

using namespace std;
using namespace sf;

// #define log(x) std::cout << x << std::endl

static const char* textControls =
    "Controls:\n"
    "Left click: place domino\n"
    "Right click: move camera\n"
    "Scroll: zoom\n"
    "A and Z: rotate\n"
    "Space: discard\n"
    "ESC: back to menu\n"
    "C: hide controls";

GameViewDomino::GameViewDomino(Win* _win, int nbOfPlayers) :
    GameView(_win, new GameDomino(nbOfPlayers), nullptr, textControls),
    curModelTile{(TileDomino*) ((GameDomino*) game)->grabTile()},
    discardTile{false},
    scoreText{new DrawText(getScores(), Color::White)} {
  curTile = new DrawDomino(curModelTile);
  curTile->setParent(&cameraObject);
  textList.push_back(scoreText);
  scoreText->setPosition(
      scoreText->getWidth() / 2 + 15, scoreText->getHeight() / 2 + 80);
  controlsText->move(0, scoreText->getHeight() + 30);
  ctrlTextPosition.y += scoreText->getHeight() + 30;
}

GameViewDomino::~GameViewDomino() {
  if (curModelTile != nullptr)
    delete curModelTile;
}

int GameViewDomino::onKeyPress(Event& event) {
  switch (event.key.code) {
    case Keyboard::Space: {
      if (!game->isOver())
        discardTile = true;
      break;
    }
    default: { break; }
  }
  return 0;
}

void GameViewDomino::changeState() {
  if (leftRotPress)
    curModelTile->rotateCounterClockwise();

  if (rightRotPress)
    curModelTile->rotateClockwise();

  if (discardTile) {
    updateTextOnScreen = true;
    destRot = 0;
    curRot = 0;
    modelRot = 0;
    leftRotPress = false;
    rightRotPress = false;
    ((GameDomino*) game)->discardTile(curModelTile);
    delete curTile;
    curTile = nullptr;
    if (!game->isOver()) {
      curModelTile = (TileDomino*) ((GameDomino*) game)->grabTile();
      curTile = new DrawDomino(curModelTile);
      curTile->setParent(&cameraObject);
    } else {
      curTile = nullptr;
      curModelTile = nullptr;
    }
    discardTile = false;
  }

  if (validM1Press) {
    updateTextOnScreen = true;
    if (!game->isOver()) {
      // sets position to 0,0 if it's the first play
      vec2i aPos;
      if (firstPlay) {
        aPos = vec2i(0, 0);
        firstPlay = false;
      } else {
        aPos = coordToGridPos(mousePos);
      }

      // try to put tile in model
      bool b = game->placeTile(curModelTile, aPos.x, aPos.y);

      // if successful, add tile to view
      if (b) {
        destRot = 0;
        curRot = 0;
        leftRotPress = false;
        rightRotPress = false;
        addTile(curTile, aPos.x, aPos.y, modelRot * 90);
        modelRot = 0;
        if (!game->isOver()) {
          curModelTile = (TileDomino*) ((GameDomino*) game)->grabTile();
          curTile = new DrawDomino(curModelTile);
          curTile->setParent(&cameraObject);
        } else {
          curTile = nullptr;
          curModelTile = nullptr;
        }
        scoreText->setText(getScores());
      }
    }
    validM1Press = false;
  }

  GameView::changeState();
}
