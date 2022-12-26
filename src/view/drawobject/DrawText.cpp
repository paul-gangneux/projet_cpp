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
  // width = textObject->getLocalBounds().width;
  // height = textObject->getLocalBounds().height;
  center = vec2f{15, 15};
  // updateTransform();
}

DrawText::DrawText(string txt) :
    DrawText(DrawText::createText(txt, sf::Color::Black, 30)) {}

DrawText::DrawText(string txt, int size) :
    DrawText(DrawText::createText(txt, sf::Color::Black, size)) {}

DrawText::DrawText(string txt, Color color, int size) :
    DrawText(DrawText::createText(txt, color, size)) {}

DrawText::~DrawText() {}

void DrawText::setText(const char* str) {
  textObject->setString(str);
  // width = textObject->getLocalBounds().width;
  // height = textObject->getLocalBounds().height;
  // center = vec2f{width / 2, height / 2};
  // updateTransform();
}

void DrawText::setText(string str) {
  textObject->setString(str);
  // width = textObject->getLocalBounds().width;
  // height = textObject->getLocalBounds().height;
  // center = vec2f{width / 2, height / 2};
  // updateTransform();
}

void DrawText::setColor(sf::Color color) {
  textObject->setColor(color);
}

float DrawText::getWidth() const {
  return textObject->getLocalBounds().width;
}

float DrawText::getHeight() const {
  return textObject->getLocalBounds().height;
}