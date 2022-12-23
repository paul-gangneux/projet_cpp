#include "view/gameview/GameViewDomino.hpp"
#include "model/game/GameDomino.hpp"
#include "view/drawobject/DrawDomino.hpp"

using namespace std;
using namespace sf;

GameViewDomino::GameViewDomino(Win* _win) :
    GameView(_win, new GameDomino(), nullptr),
    curModelTile{(TileDomino*) ((GameDomino*) game)->grabTile()} {
  curTile = new DrawDomino(curModelTile);
}

GameViewDomino::~GameViewDomino() {}

int GameViewDomino::onKeyPress(Event& event) {
  switch (event.key.code) {
    case Keyboard::Space: {
      ((GameDomino*) game)->discardTile(curModelTile);
      delete curTile;
      curTile = nullptr;
      break;
    }

    default: { break; }
  }
  return 0;
}

void GameViewDomino::changeState() {
  GameView::changeState();

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
        addTile(curTile, aPos.x, aPos.y);
        if (!game->isOver()) {
          curModelTile = (TileDomino*) ((GameDomino*) game)->grabTile();
          curTile = new DrawDomino(curModelTile);
        }

      } else {
        // todo
      }
    }
    validM1Press = false;
  }

  if (game->isOver()) {
    // todo
  }
}
