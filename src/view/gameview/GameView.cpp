#include "view/gameview/GameView.hpp"
#include "model/game/GameTrax.hpp"
#include "model/tile/TileTrax.hpp"
#include "view/drawobject/DrawTrax.hpp"

using namespace std;
using namespace sf;

#define ABS(x) ((x >= 0) ? (x) : -(x))
#define SIGN(x) ((x >= 0) ? 1 : -1)

#define TILE_SIZE 200
#define BORDER_WIDTH 8

GameView::GameView(Win* _win, DrawObject* firstTile, Game* _game) :
    DrawableState(_win),
    rootObj{DrawObject()},
    tilePlacementVisual{initTilePlacementVisual()},
    curTile{firstTile},
    objects{list<DrawObject*>()},
    game{_game},
    oldMousePos{Mouse::getPosition(*win)},
    mousePos{oldMousePos},
    deltaMouse{vec2i{0, 0}},
    validM1Press{false},
    validM2Press{false},
    leftRotPress{false},
    rightRotPress{false},
    firstPlay{true},
    curRot{0},
    destRot{0},
    modelRot{0} {
  win->setRootObject(&rootObj);
  rootObj.setPosition(win->getWidth() / 2, win->getHeight() / 2);
  curTile->setParent(&rootObj);
}

GameView::~GameView() {
  clearObjects();
  delete curTile;
  delete game;
}

DrawObject* GameView::initTilePlacementVisual() {
  int rec_width = TILE_SIZE - (BORDER_WIDTH * 2);

  RectangleShape* rect = new RectangleShape(vec2f(rec_width, rec_width));
  rect->setFillColor(Color(0, 0, 0, 0));
  rect->setOutlineThickness(BORDER_WIDTH);
  rect->setOutlineColor(Color(250, 150, 100));

  DrawObject* d = new DrawObject(rect);
  d->setParent(&rootObj);
  d->setCenter(rec_width / 2, rec_width / 2);
  d->setPosition(0, 0);
  return d;
}

void GameView::addObject(DrawObject* o) {
  o->setParent(&rootObj);
  objects.push_back(o);
}

void GameView::addTile(DrawObject* o, int x, int y) {
  o->setParent(&rootObj);
  o->setPosition(x * TILE_SIZE, y * TILE_SIZE);
  objects.push_back(o);
}

void GameView::addTile(DrawObject* o, int x, int y, float rotation) {
  addTile(o, x, y);
  o->rotate(rotation);
}

// takes mouse coordinates and changes it to coords
// the tile would have on the grid in the model
vec2i GameView::coordToGridPos(vec2i coords) {
  vec2f pos = vec2f(coords.x, coords.y);
  pos -= rootObj.getPosition();
  pos.x += (TILE_SIZE / 2.0f) * rootObj.getSize().x;
  pos.y += (TILE_SIZE / 2.0f) * rootObj.getSize().y;
  pos /= (float) TILE_SIZE;
  pos /= rootObj.getSize().x;

  if (pos.x < 0.0f)
    pos.x -= 1;

  if (pos.y < 0.0f)
    pos.y -= 1;

  vec2i ret = vec2i(pos.x, pos.y);
  return ret;
}

void GameView::clearObjects() {
  while (!objects.empty()) {
    DrawObject* o = objects.front();
    objects.pop_front();
    delete o;
  }
}

int GameView::handleEvents(sf::Event& event) {
  // updating mouse position
  deltaMouse = mousePos - oldMousePos;
  oldMousePos = mousePos;
  mousePos = Mouse::getPosition(*win);

  while (win->pollEvent(event)) {
    switch (event.type) {
      case Event::MouseButtonPressed: {
        if (win->hasFocus() && mousePos.x >= 0 && mousePos.y >= 0 &&
            mousePos.x < win->getWidth() && mousePos.y < win->getHeight()) {
          switch (event.mouseButton.button) {
            // placing a tile
            case Mouse::Button::Left: {
              validM1Press = true;
              break;
            }

            case Mouse::Button::Right:
              validM2Press = true;
              break;

            default:
              break;
          }
        }
        break;
      }

      case Event::MouseButtonReleased: {
        if (event.mouseButton.button == Mouse::Button::Right) {
          validM2Press = false;
        }
        break;
      }

      case Event::KeyPressed: {
        switch (event.key.code) {
          case Keyboard::A: {
            leftRotPress = true;
            break;
          }

          case Keyboard::E: {
            rightRotPress = true;
            break;
          }

          case Keyboard::Escape: {
            return EVENT_BACK;
            break;
          }

          default:
            onKeyPress(event);
            break;
        }
      }

      case Event::MouseWheelScrolled: {
        float f = event.mouseWheelScroll.delta / 10.0f;
        rootObj.scale(
            1 + f, 1 + f, win->getWidth() / 2.0f, win->getHeight() / 2.0f);
        break;
      }

      case Event::Closed: {
        return EVENT_QUIT;
        break;
      }

      default:
        break;
    }
  }

  return 0;
}

void GameView::changeState() {
  // handling camera movement

  if (validM2Press) {
    rootObj.move(deltaMouse.x, deltaMouse.y);
  }

  // handling selected tile rotation

  if (leftRotPress) {
    modelRot--;
    if (modelRot < 0) {
      modelRot = 3;
    }
    destRot -= 90;
    leftRotPress = false;
  }

  if (rightRotPress) {
    modelRot++;
    if (modelRot > 3) {
      modelRot = 0;
    }
    destRot += 90;
    rightRotPress = false;
  }

  if (curTile != nullptr) {
    // rotates the view for the selected tile
    int r;
    if (curRot != destRot) {
      int d = ABS(curRot - destRot);
      if (d < 5) {
        r = d;
      } else {
        r = 8;
        while (d > 90) {
          r += 2;
          d -= 90;
        }
      }
      r *= SIGN(destRot - curRot);
      curTile->rotate(r);
      curRot += r;
    } else {
      curRot = 0;
      destRot = 0;
    }

    // positions the tile where the mouse is
    vec2f size = rootObj.getSize();
    vec2f pos = rootObj.getPosition();
    curTile->setPosition(
        (mousePos.x - pos.x) / size.x, (mousePos.y - pos.y) / size.y);
  }

  vec2i v = coordToGridPos(mousePos);

  if (!firstPlay) {
    tilePlacementVisual->setPosition(v.x * TILE_SIZE, v.y * TILE_SIZE);
  }
}

void GameView::draw() {
  if (!game->isOver()) {
    tilePlacementVisual->draw(win);
  }
  for (DrawObject* o : objects) {
    o->draw(win);
  }
  if (!game->isOver() && curTile != nullptr) {
    curTile->draw(win);
  }
}