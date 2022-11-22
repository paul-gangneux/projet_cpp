#include <iostream>
#include "view/DrawObject.hpp"
#include "view/Win.hpp"
#include "geometry/vectors.hpp"

using namespace sf;
using namespace std;

int main() {
  Win win(800, 600, "Gaming");

  // exemple d'affichage de texte (todo: encapsuler dans une classe)
  Font font;
  font.loadFromFile("ressource/font/VeraMono.ttf");
  Text* text = new Text();
  text->setFont(font);
  text->setString("Gaming");
  text->setCharacterSize(30);
  text->setFillColor(Color::White);
  text->setPosition(0, 0);

  // exemple d'affichage d'une tuile
  Texture texture;
  texture.loadFromFile("./ressource/trax_tile1.png"); //todo: check error
  Sprite* tile = new Sprite();
  tile->setTexture(texture);
  tile->setScale(Vector2f(0.5, 0.5));
  // tile->setOrigin(tile->getLocalBounds().width/2.0f, tile->getLocalBounds().height/2.0f);
  //tile->move(Vector2f(200, 200));

  // exemple de relation de parentage avec DrawObject
  DrawObject drawText(text);
  DrawObject drawTile(tile);
  DrawObject rootObj;
  // drawText.setParent(&rootObj);
  drawTile.setParent(&rootObj);
  drawText.setParent(&drawTile);

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
        //todo : utiliser un changement sur les coord absolues
        drawTile.move(deltaMouse);
      }
    }

    win.clear();
    drawTile.draw(win);
    drawText.draw(win);
    win.display();

    // cap at 60 fps
    sf::sleep(desiredDelay - clock.getElapsedTime());
  }

  return EXIT_SUCCESS;
}