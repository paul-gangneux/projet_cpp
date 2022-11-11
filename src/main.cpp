#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

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
  // text.setPosition(0,0);

  while (win.isOpen()) {

    Event event;
    while (win.pollEvent(event)) {
      switch (event.type) {
        case Event::Closed:
          win.close();
          break;
        default:
          break;
      }
    }
    win.clear();
    win.draw(text);
    win.display();
  }
  return EXIT_SUCCESS;
}