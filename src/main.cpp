#include <iostream>
#include <list>
#include "geometry/vectors.hpp"
#include "view/Win.hpp"
#include "view/drawobject/DrawDomino.hpp"
#include "view/drawobject/DrawText.hpp"
#include "view/drawobject/DrawTrax.hpp"
#include "view/gameview/GameMenu.hpp"
#include "view/gameview/GameViewTrax.hpp"

using namespace sf;
using namespace std;

Win* win;
DrawableState* view;

void switchView(int newView) {
  switch (newView) {
    case EVENT_SELECT_MENU:
      delete view;
      view = new GameMenu(win);
      break;
    case EVENT_SELECT_DOMINO:
      // view = new GameViewDomino(); // TODO
      break;
    case EVENT_SELECT_TRAX:
      delete view;
      view = new GameViewTrax(win);
      break;
    case EVENT_SELECT_CARCASSONE:
      // TODO
      break;

    default:
      break;
  }
}

int main() {
  win = new Win(800, 600, "game");
  view = new GameMenu(win);

  // initialising mouse position data
  vec2i oldMousePos = Mouse::getPosition(*win);
  vec2i mousePos = oldMousePos;
  vec2i deltaMouse;

  // initialising variables useful for main loop
  Clock clock;
  Time desiredDelay = seconds(1) / 60.0f;
  Event event;

  // ===== Main Loop ===== //
  bool loops = true;
  while (loops) {
    clock.restart();

    // updating mouse position
    deltaMouse = mousePos - oldMousePos;
    oldMousePos = mousePos;
    mousePos = Mouse::getPosition(*win);

    // -- Event handling -- //

    int ret = view->handleEvents(event);
    if (ret) {
      switch (ret) {
        case EVENT_QUIT:
          loops = false;
          break;
        case EVENT_BACK:
          switchView(EVENT_SELECT_MENU);
          break;
        default:
          switchView(ret);
          break;
      }
    }

    // -- state change -- //
    view->changeState();

    // -- rendering -- //
    win->clear();
    view->draw();
    win->display();

    // cap at 60 fps
    sleep(desiredDelay - clock.getElapsedTime());
  }

  delete view;
  delete win;

  return EXIT_SUCCESS;
}