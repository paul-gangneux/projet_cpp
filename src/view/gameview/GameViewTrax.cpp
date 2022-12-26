#include "view/gameview/GameViewTrax.hpp"

#include "model/game/GameTrax.hpp"
#include "model/tile/TileTrax.hpp"
#include "view/drawobject/DrawTrax.hpp"

using namespace std;
using namespace sf;

static const char* textControls =
    "Controls:\n"
    "Left click: place tile\n"
    "Right click: move camera\n"
    "Scroll: zoom\n"
    "A and Z: rotate\n"
    "Space: change tile\n"
    "ESC: back to menu\n"
    "C: hide controls";

GameViewTrax::GameViewTrax(Win* _win) :
    GameView(_win, new GameTrax(), new DrawTrax(0), textControls),
    tileType{0} {}

GameViewTrax::~GameViewTrax() {}

int GameViewTrax::onKeyPress(Event& event) {
  switch (event.key.code) {
    case Keyboard::Space: {
      tileType = (tileType == 1) ? 0 : 1;
      if (curTile != nullptr) {
        delete curTile;
      }
      curTile = new DrawTrax(tileType);
      curTile->setParent(&rootObj);
      curTile->rotate(modelRot * 90);
      curRot = 0;
      destRot = 0;
      break;
    }
    case Keyboard::Return: {
      if (game->isOver()) {
        return EVENT_BACK;
      }
      break;
    }
    default: { break; }
  }
  return 0;
}

void GameViewTrax::changeState() {
  GameView::changeState();
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
      TileTrax* tile = new TileTrax(tileType, modelRot);
      bool b = game->placeTile(tile, aPos.x, aPos.y);

      // if successful, add tile to view
      if (!b) {
        delete tile;
      }
    }
    validM1Press = false;
  }

  // add the tiles that had been placed in model (once per frame)
  int tileInfos[4];
  if (((GameTrax*) game)->getTileInfoInPlaceQueue(tileInfos)) {
    addTile(
        new DrawTrax(tileInfos[0]),
        tileInfos[1],
        tileInfos[2],
        tileInfos[3] * 90);
  }
  // we wait until all the tiles are placed before showing the end game
  else if (game->isOver()) {
    // TODO
  }
}
