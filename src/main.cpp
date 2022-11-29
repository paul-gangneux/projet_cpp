#include <iostream>
#include "view/DrawObject.hpp"
#include "view/DrawText.hpp"
#include "view/DrawDomino.hpp"
#include "view/Win.hpp"
#include "geometry/vectors.hpp"

using namespace sf;
using namespace std;

int main() {
  Win win(800, 600, "Gaming");
  win.setVerticalSyncEnabled(true);

  DrawDomino drawTile;
  DrawObject rootObj;
  drawTile.setParent(&rootObj);
  drawTile.move(win.getWidth() / 2.0f, win.getHeight() / 2.0f);
  // drawText.setParent(&drawTile);

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
        drawTile.move(deltaMouse.x * size.x, deltaMouse.y * size.y);
      }
    }

    win.clear();
    drawTile.draw(win);
    win.display();

    // cap at 60 fps
    sf::sleep(desiredDelay - clock.getElapsedTime());
  }

  return EXIT_SUCCESS;
}