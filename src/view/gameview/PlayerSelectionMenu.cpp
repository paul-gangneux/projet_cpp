#include "view/gameview/PlayerSelectionMenu.hpp"
#include "view/gameview/GameMenu.hpp"

using namespace sf;
using namespace std;

int gameToMaxPlayers(int _game) {
  switch (_game) {
    case EVENT_SELECT_DOMINO:
      return 12;
      break;

    case EVENT_SELECT_CARCASSONNE:
      return 4;
      break;

    default:
      return 12;
      break;
  }
}

PlayerSelectionMenu::PlayerSelectionMenu(
    Win* _win, int selectedGame, int* _nbOfPlayers) :
    DrawableState(_win),
    text{"Number of players:", Color::White, 42},
    textBoxes{{"2", Color::White, 42},
              {"-", Color::White, 42},
              {"+", Color::White, 42},
              {"start", Color::White, 42}},
    minPlayers{2},
    maxPlayers{gameToMaxPlayers(selectedGame)},
    selectedAction{-1},
    gameNb{selectedGame},
    nbOfPlayers{_nbOfPlayers} {
  *nbOfPlayers = 2;

  text.setParent(&rootObj);
  text.move(0, -120);

  for (int i = 0; i < 4; i++) {
    textBoxes[i].setParent(&rootObj);
    textBoxes[i].setBackgroundColor(50, 40, 100);
  }

  textBoxes[0].resize(100, 50);
  textBoxes[0].move(0, 0);

  textBoxes[1].resize(50, 50);
  textBoxes[1].move(-110, 0);

  textBoxes[2].resize(50, 50);
  textBoxes[2].move(110, 0);

  textBoxes[3].resize(300, 60);
  textBoxes[3].move(0, 120);
}

PlayerSelectionMenu::~PlayerSelectionMenu() {}

void PlayerSelectionMenu::switchSelectedAction(int action) {
  if (selectedAction == action)
    return;
  if (selectedAction != -1) {
    textBoxes[selectedAction].setBackgroundColor(50, 40, 100);
    textBoxes[selectedAction].getTextObject()->setColor(sf::Color::White);
  }
  selectedAction = action;
  if (selectedAction != -1) {
    textBoxes[selectedAction].setBackgroundColor(200, 100, 50);
  }
}

int PlayerSelectionMenu::handleEvents(sf::Event& event) {
  while (win->pollEvent(event)) {
    switch (event.type) {
      case Event::MouseButtonPressed: {
        if (event.mouseButton.button == Mouse::Button::Left) {
          switch (selectedAction) {
            case 1:
              if (*nbOfPlayers > minPlayers) {
                (*nbOfPlayers)--;
                textBoxes[0].getTextObject()->setText(
                    to_string((*nbOfPlayers)));
              }
              break;
            case 2:
              if (*nbOfPlayers < maxPlayers) {
                (*nbOfPlayers)++;
                textBoxes[0].getTextObject()->setText(
                    to_string((*nbOfPlayers)));
              }
              break;
            case 3:
              return gameNb;
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
          case Keyboard::Return: {
            return gameNb;
            break;
          }

          case Keyboard::Escape: {
            return EVENT_SELECT_MENU;
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

void PlayerSelectionMenu::changeState() {
  vec2i mousePos = Mouse::getPosition(*win);

  for (int i = 1; i <= 3; i++) {
    if (textBoxes[i].isInBox(mousePos)) {
      switchSelectedAction(i);
      break;
    } else {
      switchSelectedAction(-1);
    }
  }
}

void PlayerSelectionMenu::draw() {
  text.draw(win);
  for (int i = 0; i < 4; i++) {
    textBoxes[i].draw(win);
  }
}