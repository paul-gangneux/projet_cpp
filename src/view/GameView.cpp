#include "view/GameView.hpp"

using namespace std;
using namespace sf;

#define ABS(x) ((x>=0)?(x):-(x))
#define SIGN(x) ((x>=0)?1:-1)

GameView::GameView(int _w, int _h, const char* windowTitle) :
  rootObj{DrawObject()},
  objects{list<DrawObject*>()},
  win{_w, _h, windowTitle}
{}

GameView::~GameView()
{}

void GameView::addObject(DrawObject* o) {
  o->setParent(&rootObj);
  objects.push_back(o);
}

void GameView::addTile(DrawObject* o, int x, int y) {
  o->setParent(&rootObj);
  o->setPosition(
    x * 200 + (win.getWidth() / 2.0f),
    y * 200 + (win.getHeight() / 2.0f)
  );
  objects.push_back(o);
}

void GameView::clearObjects() {
  while (!objects.empty()) {
    DrawObject* o = objects.front();
    objects.pop_front();
    delete o;
  }
}

void GameView::viewLoop() {
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
  DrawObject* curTile = nullptr;

  // for testing
  curTile = new DrawDomino();
  curTile->setParent(&rootObj);

  // --- Main Loop ---
  while (runs) {
    clock.restart();

    // updating mouse position
    deltaMouse = mousePos - oldMousePos;
    oldMousePos = mousePos;
    mousePos = Mouse::getPosition(win);

    // -- Event handling -- 
    Event event;
    while (win.pollEvent(event)) {
      switch (event.type) {

        case Event::MouseButtonPressed: {
          if (
            mousePos.x >= 0 &&
            mousePos.y >= 0 &&
            mousePos.x < win.getWidth() &&
            mousePos.y < win.getHeight()
            ) {
            switch (event.mouseButton.button) {

              // case Mouse::Button::Left:
              //   validM1pressed = true;
              //   break;

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
              destRot -= 90;
              break;

            case Keyboard::E:
              destRot += 90;
              break;

            default:
              break;
          }
          break;
        }

        case Event::MouseWheelScrolled: {
          float f = event.mouseWheelScroll.delta / 10.0f;
          rootObj.scale(1 + f, 1 + f, win.getWidth() / 2.0f, win.getHeight() / 2.0f);
          break;
        }

        case Event::Closed: {
          runs = false;
          break;
        }

        default: {
          break;
        }
      }
    }

    // -- state change --

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
        }
        else {
          r = 5;
          while (d > 90) {
            r += 2;
            d -= 90;
          }
        }
        r *= SIGN(destRot - curRot);
        curTile->rotate(r);
        curRot += r;
      }
      else {
        curRot = 0;
        destRot = 0;
      }

      // positions the tile where the mouse is
      vec2f size = rootObj.getSize();
      vec2f pos = rootObj.getPosition();
      curTile->setPosition((mousePos.x - pos.x) / size.x, (mousePos.y - pos.y) / size.y);
    }

    // -- rendering --

    win.clear();

    for (DrawObject* o : objects) {
      o->draw(win);
    }
    if (curTile != nullptr) {
      curTile->draw(win);
    }

    win.display();

    // cap at 60 fps
    sf::sleep(desiredDelay - clock.getElapsedTime());
  }
}