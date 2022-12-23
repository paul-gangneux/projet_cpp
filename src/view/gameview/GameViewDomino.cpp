#include "view/gameview/GameViewDomino.hpp"
#include "model/game/GameDomino.hpp"
#include "view/drawobject/DrawDomino.hpp"

using namespace std;
using namespace sf;

GameViewDomino::GameViewDomino(Win* _win) :
    GameView(_win, new GameDomino(), nullptr),
    curModelTile{(TileDomino*) ((GameDomino*) game)->grabTile()},
    discardTile{false} {
  curTile = new DrawDomino(curModelTile);
  curTile->setParent(&rootObj);
}

GameViewDomino::~GameViewDomino() {}

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

  if (validM1Press) {
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
        addTile(curTile, aPos.x, aPos.y, modelRot * 90);
        modelRot = 0;
        if (!game->isOver()) {
          curModelTile = (TileDomino*) ((GameDomino*) game)->grabTile();
          curTile = new DrawDomino(curModelTile);
          curTile->setParent(&rootObj);
        } else {
          curTile = nullptr;
        }
      }
    }
    validM1Press = false;
  }

  if (discardTile) {
    destRot = 0;
    curRot = 0;
    modelRot = 0;
    ((GameDomino*) game)->discardTile(curModelTile);
    delete curTile;
    curTile = nullptr;
    if (!game->isOver()) {
      curModelTile = (TileDomino*) ((GameDomino*) game)->grabTile();
      curTile = new DrawDomino(curModelTile);
      curTile->setParent(&rootObj);
    } else {
      curTile = nullptr;
    }
    discardTile = false;
  }

  GameView::changeState();

  if (game->isOver()) {
    // todo
  }
}
