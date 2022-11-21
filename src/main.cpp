#include <iostream>
#include "view/DrawText.hpp"
#include "view/Win.hpp"
#include "geometry/vectors.hpp"

using namespace sf;
using namespace std;

int main() {
  bool mouseIsIn = true;
  // bool mousePressed = false;
  Win win(800, 600, "Gaming");

  // exemple d'affichage de texte (todo: encapsuler dans une classe)
  Font font;
  font.loadFromFile("ressource/font/VeraMono.ttf");
  Text text;
  text.setFont(font);
  text.setString("Gaming");
  text.setCharacterSize(30);
  text.setFillColor(Color::White);
  text.setPosition(0, 0);

  float tx = 0, ty = 0;

  bool runs = true;

  float dx = 0;
  float dy = 0;

  Vector2i mousePos = Mouse::getPosition(win);

  float mx = mousePos.x;
  float my = mousePos.y;

  while (runs) {

    dx = mousePos.x - mx;
    mx = mousePos.x;
    dy = mousePos.y - my;
    my = mousePos.y;
    mousePos = Mouse::getPosition(win);

    Event event;
    while (win.pollEvent(event)) {
      switch (event.type) {
        case Event::Closed:
          runs = false;
          break;
        case Event::MouseLeft:
          mouseIsIn = false;
          break;
        case Event::MouseEntered:
          mouseIsIn = true;
          break;
        default:
          break;
      }
    }

    if (win.hasFocus() && mouseIsIn) {
      if (Mouse::isButtonPressed(Mouse::Button::Left)) {
        tx += dx;
        ty += dy;
        text.move(dx, dy);
        text.setScale(sf::Vector2f(1,1));
      }
    }

    text.setString(to_string(tx) + " " + to_string(ty));

    win.clear();
    win.draw(text);
    win.display();
  }

  return EXIT_SUCCESS;
}