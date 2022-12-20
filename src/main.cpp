#include <iostream>
#include <list>
#include "geometry/vectors.hpp"
#include "view/GameView.hpp"
#include "view/Win.hpp"
#include "view/drawobject/DrawDomino.hpp"
#include "view/drawobject/DrawText.hpp"
#include "view/drawobject/DrawTrax.hpp"

using namespace sf;
using namespace std;

bool validM1pressed = false;
bool runs = true;

Event _event;

void handleEvent(Event& event, Win& win, vec2i mousePos) {
  while (win.pollEvent(event)) {
    switch (event.type) {
      case Event::MouseButtonPressed: {
        if (mousePos.x >= 0 && mousePos.y >= 0 && mousePos.x < win.getWidth() &&
            mousePos.y < win.getHeight()) {
          switch (event.mouseButton.button) {
            case Mouse::Button::Left: {
              validM1pressed = true;
              break;
            }

            default:
              break;
          }
        }
        break;
      }

      case Event::KeyPressed: {
        switch (event.key.code) {
          case Keyboard::F11: {
            // fullscreen
            break;
          }

          case Keyboard::Num1: {
            cout << "1" << endl;
            break;
          }

          case Keyboard::Num2: {
            cout << "2" << endl;
            break;
          }

          case Keyboard::Num3: {
            cout << "3" << endl;
            break;
          }

          case Keyboard::Escape: {
            runs = false;
            break;
          }

          default:
            break;
        }
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
}

int main() {
  
  Win win{800, 600, "game"};
  GameView view{&win};

  // initialising mouse position data
  vec2i oldMousePos = Mouse::getPosition(win);
  vec2i mousePos = oldMousePos;
  vec2i deltaMouse;

  // initialising variables useful for main loop
  sf::Clock clock;
  sf::Time desiredDelay = sf::seconds(1) / 60.0f;

  // --- for testing ---

  DrawText debugText(" 1. domino\n 2. trax\n 3. carcassone", Color::White);

  // ===== Main Loop ===== //

  while (runs) {
    clock.restart();

    // updating mouse position
    deltaMouse = mousePos - oldMousePos;
    oldMousePos = mousePos;
    mousePos = Mouse::getPosition(win);

    // -- Event handling -- //

    handleEvent(_event, win, mousePos);

    // -- state change -- //

    if (win.hasFocus()) {
      if (validM1pressed) {
        validM1pressed = false;
      }
    }

    win.clear();
    debugText.draw(win);
    win.display();

    // cap at 60 fps
    sf::sleep(desiredDelay - clock.getElapsedTime());
  }

  return EXIT_SUCCESS;
}