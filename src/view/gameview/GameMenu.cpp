#include "view/gameview/GameMenu.hpp"
#include <cmath>

#define ABS(x) (x >= 0 ? x : -x)

using namespace sf;

GameMenu::GameMenu(Win* _win) :
    DrawableState(_win),
    menuText{"1. domino\n\n2. trax\n\n3. carcassone", Color::White, 42} {
  menuText.setParent(&rootObj);
  menuText.move(-menuText.getWidth() / 2, -menuText.getHeight() / 2);
}

GameMenu::~GameMenu() {}

int GameMenu::handleEvents(sf::Event& event) {
  while (win->pollEvent(event)) {
    switch (event.type) {
      case Event::KeyPressed: {
        switch (event.key.code) {
          case Keyboard::Num1: {
            return EVENT_SELECT_DOMINO;
            break;
          }

          case Keyboard::Num2: {
            return EVENT_SELECT_TRAX;
            break;
          }

          case Keyboard::Num3: {
            return EVENT_SELECT_CARCASSONE;
            break;
          }

          case Keyboard::Escape: {
            return EVENT_QUIT;
            break;
          }

            // case Keyboard::F11: {
            //   // fullscreen
            //   break;
            // }

          default:
            break;
        }
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
void GameMenu::changeState() {
  static float i = 1;
  i += 0.03f;
  menuText.setColor(Color(
      ABS(sin(i)) * 255,
      ABS(sin(i * 1.3)) * 200 + 55,
      ABS(sin(i * 2.7)) * 255));
}
void GameMenu::draw() {
  menuText.draw(win);
}