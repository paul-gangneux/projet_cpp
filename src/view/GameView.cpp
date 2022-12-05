#include "view/GameView.hpp"

using namespace std;
using namespace sf;

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
  bool validM1pressed = false;

  // --- Main Loop ---
  while (runs) {
    clock.restart();

    // updating mouse position
    deltaMouse = mousePos - oldMousePos;
    oldMousePos = mousePos;
    mousePos = Mouse::getPosition(win);

    Event event;
    while (win.pollEvent(event)) {
      switch (event.type) {
        case Event::Closed: {
          runs = false;
          break;
        }
        case Event::MouseButtonPressed: {
          switch (event.mouseButton.button) {
            case Mouse::Button::Left: {
              if (mousePos.x >= 0 &&
                mousePos.y >= 0 &&
                mousePos.x < win.getWidth() &&
                mousePos.y < win.getHeight())
              {
                validM1pressed = true;
              }
              break;
            }
            default:
              break;
          }
          break;
        }
        case Event::MouseButtonReleased: {
          switch (event.mouseButton.button) {
            case Mouse::Button::Left: {
              validM1pressed = false;
              break;
            }
            default:
              break;
          }
        default:
          break;
        }
        case Event::MouseWheelScrolled: {
          float f = event.mouseWheelScroll.delta / 10.0f;
          rootObj.scale(1 + f, 1 + f, win.getWidth() / 2.0f, win.getHeight() / 2.0f);
          break;
        }
      }
    }

    if (win.hasFocus()) {
      if (validM1pressed) {
        vec2f size = rootObj.getSize();
        size.x = 1.0f / size.x;
        size.y = 1.0f / size.y;
        rootObj.move(deltaMouse.x, deltaMouse.y);
      }
    }

    win.clear();
    for (DrawObject* o : objects) {
      o->draw(win);
    }
    win.display();

    // cap at 60 fps
    sf::sleep(desiredDelay - clock.getElapsedTime());
  }
}