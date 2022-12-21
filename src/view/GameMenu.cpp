#include "view/GameMenu.hpp"

using namespace sf;

GameMenu::GameMenu(Win* _win) :
    DrawableState(_win),
    menuText{" 1. domino\n 2. trax\n 3. carcassone", Color::White} {}

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
  // todo
}
void GameMenu::draw() {
  menuText.draw(win);
}