#include "view/gameview/GameView.hpp"

#include <algorithm>
#include "model/game/GameTrax.hpp"
#include "model/tile/TileTrax.hpp"
#include "view/drawobject/DrawTrax.hpp"
#include "view/drawobject/TextBox.hpp"

using namespace std;
using namespace sf;

#define ABS(x) ((x >= 0) ? (x) : -(x))
#define SIGN(x) ((x >= 0) ? 1 : -1)

#define TILE_SIZE 200
#define BORDER_WIDTH 8

static const char* showControlsText = "Press C to\nshow controls";

GameView::GameView(
    Win* _win, Game* _game, DrawObject* firstTile, const char* _ctrlText) :
    DrawableState(_win),
    game{_game},
    cameraObject{DrawObject()},
    tilePlacementVisual{initTilePlacementVisual()},
    curTile{firstTile},
    topLeftText{new DrawText("", Color::White)},
    controlsText{new DrawText(showControlsText, Color::White, 24)},
    objects{list<DrawObject*>()},
    textList{list<DrawObject*>()},
    oldMousePos{Mouse::getPosition(*win)},
    mousePos{oldMousePos},
    deltaMouse{vec2i{0, 0}},
    validM1Press{false},
    validM2Press{false},
    leftRotPress{false},
    rightRotPress{false},
    firstPlay{true},
    controlsAreShown{false},
    curRot{0},
    destRot{0},
    modelRot{0},
    ctrlText{_ctrlText},
    ctrlTextPosition{15, 100},
    gameIsOver{false} {
  cameraObject.setParent(&rootObj);
  // cameraObject.setPosition(rootObj.getPosition());

  if (curTile != nullptr)
    curTile->setParent(&cameraObject);
  textList.push_back(topLeftText);
  textList.push_back(controlsText);
  controlsText->setPosition(
      controlsText->getWidth() / 2 + ctrlTextPosition.x,
      controlsText->getHeight() / 2 + ctrlTextPosition.y);
}

GameView::~GameView() {
  clearObjects();
  clearText();
  delete curTile;
  delete game;
  delete tilePlacementVisual;
}

DrawObject* GameView::initTilePlacementVisual() {
  int rec_width = TILE_SIZE - (BORDER_WIDTH * 2);

  RectangleShape* rect = new RectangleShape(vec2f(rec_width, rec_width));
  rect->setFillColor(Color(0, 0, 0, 0));
  rect->setOutlineThickness(BORDER_WIDTH);
  rect->setOutlineColor(Color(250, 150, 100));

  DrawObject* d = new DrawObject(rect);
  d->setParent(&cameraObject);
  d->setCenter(rec_width / 2, rec_width / 2);
  d->setPosition(0, 0);
  return d;
}

void GameView::addObject(DrawObject* o) {
  o->setParent(&cameraObject);
  objects.push_back(o);
}

void GameView::addTile(DrawObject* o, int x, int y) {
  o->setParent(&cameraObject);
  o->setPosition(x * TILE_SIZE, y * TILE_SIZE);
  objects.push_back(o);
}

void GameView::addTile(DrawObject* o, int x, int y, float rotation) {
  addTile(o, x, y);
  o->setRotation(rotation);
}

// takes mouse coordinates and changes it to coords
// the tile would have on the grid in the model
vec2i GameView::coordToGridPos(vec2i coords) {
  vec2f pos = vec2f(coords.x, coords.y);
  pos -= cameraObject.getAbsolutePosition();
  pos.x += (TILE_SIZE / 2.0f) * cameraObject.getSize().x;
  pos.y += (TILE_SIZE / 2.0f) * cameraObject.getSize().y;
  pos /= (float) TILE_SIZE;
  pos /= cameraObject.getSize().x;

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

void GameView::clearText() {
  while (!textList.empty()) {
    DrawObject* o = textList.front();
    textList.pop_front();
    delete o;
  }
}

int GameView::handleEvents(sf::Event& event) {
  // updating mouse position
  deltaMouse = mousePos - oldMousePos;
  oldMousePos = mousePos;
  mousePos = Mouse::getPosition(*win);

  while (win->pollEvent(event)) {
    switch (event.type) {
      case Event::MouseButtonPressed: {
        if (win->hasFocus() && mousePos.x >= 0 && mousePos.y >= 0 &&
            mousePos.x < win->getWidth() && mousePos.y < win->getHeight()) {
          switch (event.mouseButton.button) {
            // placing a tile
            case Mouse::Button::Left: {
              validM1Press = true;
              break;
            }

            case Mouse::Button::Right:
              validM2Press = true;
              break;

            default:
              break;
          }
        }
        break;
      }

      case Event::MouseButtonReleased: {
        if (event.mouseButton.button == Mouse::Button::Right) {
          validM2Press = false;
        }
        break;
      }

      case Event::KeyPressed: {
        switch (event.key.code) {
          case Keyboard::A: {
            leftRotPress = true;
            break;
          }

          case Keyboard::Z: {
            rightRotPress = true;
            break;
          }

          case Keyboard::C: {
            if (controlsAreShown)
              controlsText->setText(showControlsText);
            else
              controlsText->setText(ctrlText);

            controlsAreShown = !controlsAreShown;
            controlsText->setPosition(
                controlsText->getWidth() / 2 + ctrlTextPosition.x,
                controlsText->getHeight() / 2 + ctrlTextPosition.y);

            break;
          }

          case Keyboard::Escape: {
            return EVENT_BACK;
            break;
          }

          case Keyboard::Return: {
            if (game->isOver()) {
              return EVENT_BACK;
            }
            break;
          }

          default:
            return onKeyPress(event);
            break;
        }
        break;
      }

      case Event::MouseWheelScrolled: {
        float f = event.mouseWheelScroll.delta / 10.0f;
        cameraObject.scale(1 + f, 1 + f);
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

void GameView::changeState() {
  // handling camera movement

  if (validM2Press) {
    cameraObject.move(deltaMouse.x, deltaMouse.y);
  }

  // handling selected tile rotation

  if (leftRotPress) {
    modelRot--;
    if (modelRot < 0) {
      modelRot = 3;
    }
    destRot -= 90;
    leftRotPress = false;
  }

  if (rightRotPress) {
    modelRot++;
    if (modelRot > 3) {
      modelRot = 0;
    }
    destRot += 90;
    rightRotPress = false;
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

    // positions the held tile where the mouse is
    vec2f size = cameraObject.getSize();
    vec2f pos = cameraObject.getAbsolutePosition();
    curTile->setPosition(
        (mousePos.x - pos.x) / size.x, (mousePos.y - pos.y) / size.y);
  }

  vec2i v = coordToGridPos(mousePos);

  // positionning the square showing where the tile will be placed
  if (!firstPlay) {
    tilePlacementVisual->setPosition(v.x * TILE_SIZE, v.y * TILE_SIZE);
  }

  if (!game->isOver()) {
    topLeftText->setText("Turn: " + game->getCurrentPlayer()->getName());
    topLeftText->setPosition(
        topLeftText->getWidth() / 2 + 15, topLeftText->getHeight() / 2 + 10);
  } else if (!gameIsOver) {
    topLeftText->setText("Game Ended, press ENTER to go back");
    topLeftText->setPosition(
        topLeftText->getWidth() / 2 + 15, topLeftText->getHeight() / 2 + 10);
    onGameEnd();
    gameIsOver = true;
  }
}

void GameView::draw() {
  if (!game->isOver()) {
    tilePlacementVisual->draw(win);
  }
  for (DrawObject* o : objects) {
    o->draw(win);
  }
  if (!game->isOver() && curTile != nullptr) {
    curTile->draw(win);
  }
  for (DrawObject* t : textList) {
    t->draw(win);
  }
}

string GameView::getScores() const {
  string s = "Scores:\n";
  std::vector<Player*> ps = game->getPlayers();
  for (uint i = 0; i < ps.size() - 1; i++) {
    s += ps.at(i)->getName() + ": " + to_string(ps.at(i)->getScore()) + "\n";
  }
  if (ps.size() > 0) {
    s += ps.back()->getName() + ": " + to_string(ps.back()->getScore());
  }
  return s;
}

vector<string> GameView::getWinners() const {
  std::vector<Player*> ps = game->getPlayers();
  sort(ps.begin(), ps.end(), [](Player* p1, Player* p2) {
    return p1->getScore() > p2->getScore();
  });
  vector<string> vec = vector<string>();
  int score = (ps.front())->getScore();
  if (score == 0)
    return vec;  // nobody wins, empty vector
  for (Player* p : ps) {
    if (score == p->getScore())
      vec.push_back(p->getName());
    else
      break;
  }
  return vec;
}

void GameView::onGameEnd() {
  vector<string> strs = getWinners();
  string s;
  if (strs.size() == 1) {
    s = "Winner: " + strs[0] + "!";
  } else if (strs.size() == 0) {
    s = "Nobody wins...";
  } else {
    s = "Winners: ";
    for (size_t i = 0; i < strs.size() - 1; i++) {
      s += strs.at(i) + ", ";
    }
    s += strs.at(strs.size() - 1) + "!";
  }
  TextBox* box = new TextBox(s, Color::White, 42);
  box->setFillColor(Color(10, 20, 80, 160));
  box->setOutlineColor(Color(20, 40, 100, 255));
  box->setParent(&rootObj);
  textList.push_back(box);
};