#include "view/drawobject/DrawText.hpp"

using namespace sf;
using namespace std;

Font initFont() {
  Font font;
  font.loadFromFile("ressource/font/VeraMono.ttf");
  return font;
}

Font DrawText::font = initFont();

Text* DrawText::createText(string str, Color color, int size) {
  Text* text = new Text();
  text->setFont(DrawText::font);
  text->setString(str);
  text->setCharacterSize(size);
  text->setFillColor(color);
  text->setPosition(0, 0);
  return text;
}

DrawText::DrawText(Text* obj) : DrawObject(obj), textObject{obj} {
  recenter();
}

DrawText::DrawText(const char* txt) : DrawText(string(txt)) {}

DrawText::DrawText(string txt) :
    DrawText(DrawText::createText(txt, sf::Color::Black, 30)) {}

DrawText::DrawText(string txt, int size) :
    DrawText(DrawText::createText(txt, sf::Color::Black, size)) {}

DrawText::DrawText(string txt, Color color, int size) :
    DrawText(DrawText::createText(txt, color, size)) {}

DrawText::~DrawText() {}

void DrawText::setText(const char* str) {
  textObject->setString(str);
  recenter();
}

void DrawText::setText(string str) {
  textObject->setString(str);
  recenter();
}

void DrawText::setColor(sf::Color color) {
  textObject->setFillColor(color);
}

float DrawText::getWidth() const {
  return textObject->getLocalBounds().width;
}

float DrawText::getHeight() const {
  return textObject->getLocalBounds().height;
}

void DrawText::recenter() {
  float width = textObject->getLocalBounds().width;
  float height = textObject->getLocalBounds().height;
  float left = textObject->getLocalBounds().left;
  float top = textObject->getLocalBounds().top;
  setCenter(width / 2.0f + left, height / 2.0f + top);
}