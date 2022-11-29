#include "view/DrawText.hpp"

using namespace sf;
using namespace std;

Font initFont() {
  Font font;
  font.loadFromFile("ressource/font/VeraMono.ttf");
  return font;
}

Font DrawText::font = initFont();

Text* DrawText::createText(string str, Color color) {
  Text* text = new Text();
  text->setFont(DrawText::font);
  text->setString(str);
  text->setCharacterSize(30);
  text->setFillColor(color);
  text->setPosition(0, 0);
  return text;
}

DrawText::DrawText(Text* obj) :
  DrawObject(obj),
  textObject{obj}
{}

DrawText::DrawText(string txt) :
  DrawText(DrawText::createText(txt))
{}

DrawText::DrawText(string txt, Color color) :
  DrawText(DrawText::createText(txt, color))
{}

DrawText::~DrawText() {}