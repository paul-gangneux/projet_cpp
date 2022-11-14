#include <SFML/Graphics.hpp>
#include <iostream>
#include "view/DrawText.hpp"
using namespace sf;
using namespace std;

int main() {
  RenderWindow win(VideoMode(800, 600, 32), "Gaming");

  // exemple d'affichage de texte (todo: encapsuler dans une classe)
  Font font;
  font.loadFromFile("ressource/font/VeraMono.ttf");
  Text text;
  text.setFont(font);
  text.setString("Gaming");
  text.setCharacterSize(100);
  text.setFillColor(Color::White);
  text.setPosition(0,0);

  bool runs = true;

  while (runs) {

    Event event;
    while (win.pollEvent(event)) {
      switch (event.type) {
        case Event::Closed:
          runs = false;
          break;
        default:
          break;
      }
    }
    win.clear();
    win.draw(text);
    win.display();
  }

  
  win.close();
  return EXIT_SUCCESS;
}