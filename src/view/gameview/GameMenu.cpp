#include "view/gameview/GameMenu.hpp"
#include <cmath>
#include <iostream>

#define ABS(x) (x >= 0 ? x : -x)

using namespace sf;
using namespace std;

static float funnyColor;

GameMenu::GameMenu(Win* _win) :
    DrawableState(_win),
    menuTextBoxes{{"Domino", Color::White, 42},
                  {"Trax", Color::White, 42},
                  {"Carcassonne", Color::White, 42}},
    selectedAction{-1} {
  for (int i = 0; i < 3; i++) {
    menuTextBoxes[i].setParent(&rootObj);
    menuTextBoxes[i].resize(400, 60);
    menuTextBoxes[i].move(0, 140 * (i - 1));
    menuTextBoxes[i].setBackgroundColor(50, 40, 100);
    funnyColor = 1;
  }
}

GameMenu::~GameMenu() {}

void GameMenu::switchSelectedAction(int action) {
  if (selectedAction == action)
    return;
  if (selectedAction != -1) {
    menuTextBoxes[selectedAction].setBackgroundColor(50, 40, 100);
    menuTextBoxes[selectedAction].getTextObject()->setColor(sf::Color::White);
  }
  selectedAction = action;
  if (selectedAction != -1) {
    menuTextBoxes[selectedAction].setBackgroundColor(200, 100, 50);
  }
}

int GameMenu::handleEvents(sf::Event& event) {
  while (win->pollEvent(event)) {
    switch (event.type) {
      case Event::MouseButtonPressed: {
        if (event.mouseButton.button == Mouse::Button::Left) {
          switch (selectedAction) {
            case 0:
              return EVENT_SELECT_DOMINO_PLAYERSELECT;
              break;
            case 1:
              return EVENT_SELECT_TRAX;
              break;
            case 2:
              return EVENT_SELECT_CARCASSONNE_PLAYERSELECT;
              break;

            default:
              return 0;
              break;
          }
        }
        break;
      }
      case Event::KeyPressed: {
        switch (event.key.code) {
          case Keyboard::Num1: {
            return EVENT_SELECT_DOMINO_PLAYERSELECT;
            break;
          }

          case Keyboard::Num2: {
            return EVENT_SELECT_TRAX;
            break;
          }

          case Keyboard::Num3: {
            return EVENT_SELECT_CARCASSONNE_PLAYERSELECT;
            break;
          }

          case Keyboard::Escape: {
            return EVENT_QUIT;
            break;
          }

          case Keyboard::F11: {
            return EVENT_FULLSCREEN;
            break;
          }

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
  vec2i mousePos = Mouse::getPosition(*win);

  for (int i = 0; i < 3; i++) {
    if (menuTextBoxes[i].isInBox(mousePos)) {
      switchSelectedAction(i);
      break;
    } else {
      switchSelectedAction(-1);
    }
  }

  funnyColor += 0.03f;
  if (selectedAction != -1) {
    for (int i = 0; i < 3; i++) {
      menuTextBoxes[selectedAction].getTextObject()->setColor(Color(
          ABS(sin(i + funnyColor)) * 255,
          ABS(sin(i + funnyColor * 1.3)) * 200 + 55,
          ABS(sin(i + funnyColor * 2.7)) * 255));
    }
  }
}
void GameMenu::draw() {
  for (int i = 0; i < 3; i++) {
    menuTextBoxes[i].draw(win);
  }
}