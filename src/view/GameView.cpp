#include "view/GameView.hpp"
#include "model/game/GameTrax.hpp"
#include "model/tile/TileTrax.hpp"
#include "view/drawobject/DrawTrax.hpp"

using namespace std;
using namespace sf;

#define ABS(x) ((x >= 0) ? (x) : -(x))
#define SIGN(x) ((x >= 0) ? 1 : -1)

#define TILE_SIZE 200
#define BORDER_WIDTH 8

GameView::GameView(int _w, int _h, const char* windowTitle) :
    rootObj{DrawObject()},
    objects{list<DrawObject*>()},
    win{_w, _h, windowTitle, &rootObj} {
  rootObj.setPosition(_w / 2, _h / 2);
}

GameView::~GameView() {}

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
  pos /= (float)TILE_SIZE;
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

void GameView::viewLoop() {
  // game data (TODO, generalize)
  GameTrax game;
  int tileType = 1;
  bool firstPlay = true;

  // initialising mouse position data
  vec2i oldMousePos = Mouse::getPosition(win);
  vec2i mousePos = oldMousePos;
  vec2i deltaMouse;

  // initialising variables useful for main loop
  sf::Clock clock;
  sf::Time desiredDelay = sf::seconds(1) / 60.0f;
  bool runs = true;
  // bool validM1pressed = false;
  bool validM2pressed = false;

  int curRot = 0;
  int destRot = 0;
  int modelRot = 0;
  DrawObject* curTile = nullptr;
  DrawObject* potentialTile = nullptr;

  // --- for testing ---

  curTile = new DrawTrax(tileType, curRot);
  curTile->setParent(&rootObj);

  DrawText debugText("", Color::White);

  // potentialTile = new DrawTrax(2, true);

  int rec_width = TILE_SIZE - (BORDER_WIDTH * 2);
  sf::RectangleShape* rect = new RectangleShape(vec2f(rec_width, rec_width));
  rect->setFillColor(sf::Color(0, 0, 0, 0));
  rect->setOutlineThickness(BORDER_WIDTH);
  rect->setOutlineColor(sf::Color(250, 150, 100));

  potentialTile = new DrawObject(rect);
  potentialTile->setParent(&rootObj);
  potentialTile->setCenter(rec_width / 2, rec_width / 2);
  potentialTile->setPosition(0, 0);

  // ===== Main Loop ===== //

  while (runs) {
    clock.restart();

    // updating mouse position
    deltaMouse = mousePos - oldMousePos;
    oldMousePos = mousePos;
    mousePos = Mouse::getPosition(win);

    // -- Event handling -- //

    Event event;
    while (win.pollEvent(event)) {
      switch (event.type) {
        case Event::MouseButtonPressed: {
          if (mousePos.x >= 0 && mousePos.y >= 0 &&
              mousePos.x < win.getWidth() && mousePos.y < win.getHeight()) {
            switch (event.mouseButton.button) {
              // placing a tile
              case Mouse::Button::Left: {
                if (!game.isOver()) {
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
                  bool b = game.placeTile(tile, aPos.x, aPos.y);

                  // if successful, add tile to view
                  if (!b) {
                    delete tile;
                  }
                }

                break;
              }

              case Mouse::Button::Right:
                validM2pressed = true;
                break;

              default:
                break;
            }
          }
          break;
        }

        case Event::MouseButtonReleased: {
          switch (event.mouseButton.button) {
              // case Mouse::Button::Left:
              //   validM1pressed = false;
              //   break;

            case Mouse::Button::Right:
              validM2pressed = false;
              break;

            default:
              break;
          }
          break;
        }

        case Event::KeyPressed: {
          switch (event.key.code) {
            case Keyboard::A:
              modelRot--;
              if (modelRot < 0) {
                modelRot = 3;
              }
              destRot -= 90;
              if (potentialTile != nullptr) {
                potentialTile->rotate(-90);
              }
              break;

            case Keyboard::E:
              modelRot++;
              if (modelRot > 3) {
                modelRot = 0;
              }
              if (potentialTile != nullptr) {
                potentialTile->rotate(90);
              }
              destRot += 90;
              break;

            case Keyboard::Space:
              tileType = (tileType == 1) ? 0 : 1;
              if (curTile != nullptr) {
                delete curTile;
              }

              curTile = new DrawTrax(tileType);
              curTile->setParent(&rootObj);
              curTile->rotate(modelRot * 90);
              curRot = 0;
              destRot = 0;

            default:
              break;
          }
          break;
        }

        case Event::MouseWheelScrolled: {
          float f = event.mouseWheelScroll.delta / 10.0f;
          rootObj.scale(
              1 + f, 1 + f, win.getWidth() / 2.0f, win.getHeight() / 2.0f);
          break;
        }

        case Event::Closed: {
          runs = false;
          break;
        }

        default:
          break;
      }
    }

    // -- state change -- //

    if (win.hasFocus()) {
      if (validM2pressed) {
        rootObj.move(deltaMouse.x, deltaMouse.y);
      }
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
    debugText.setText(to_string(v.x) + " " + to_string(v.y));

    if (!firstPlay) {
      potentialTile->setPosition(v.x * TILE_SIZE, v.y * TILE_SIZE);
    }

    int tileInfos[4];
    if (game.getTileInfoInPlaceQueue(tileInfos)) {
      addTile(
          new DrawTrax(tileInfos[0]),
          tileInfos[1],
          tileInfos[2],
          tileInfos[3] * 90);
    }
    // we wait until all the tiles are placed before showing the end game
    else if (game.isOver()) {
      debugText.setText("Game over");
      // TODO
    }

    // -- rendering -- //

    win.clear();

    if (!game.isOver()) {
      potentialTile->draw(win);
    }
    for (DrawObject* o : objects) {
      o->draw(win);
    }
    if (!game.isOver() && curTile != nullptr) {
      curTile->draw(win);
    }
    debugText.draw(win);

    win.display();

    // cap at 60 fps
    sf::sleep(desiredDelay - clock.getElapsedTime());
  }

  // todo: necessary frees
}