#include "view/drawobject/TextBox.hpp"

#define MAX(a, b) ((a) >= (b) ? a : b)

#define default_outline_size 2

using namespace sf;
using namespace std;

TextBox::TextBox(std::string _text, sf::Color fontColor, int fontSize) :
    DrawObject(initRect()),
    text{new DrawText(_text, fontColor, fontSize)},
    width{1},
    height{1},
    padding{10},
    outlineSize{default_outline_size} {
  resize(0, 0);
  text->setParent(this);
}

TextBox::TextBox(const char* _text) : TextBox(string(_text)) {}

TextBox::~TextBox() {
  delete text;
}

DrawText* TextBox::getTextObject() {
  return text;
}

float TextBox::getWidth() const {
  return width + 2 * (padding + outlineSize);
}

float TextBox::getHeight() const {
  return height + 2 * (padding + outlineSize);
}

RectangleShape* TextBox::initRect() {
  rect = new RectangleShape();
  rect->setFillColor(Color(0, 0, 0, 100));
  rect->setOutlineThickness(default_outline_size);
  rect->setOutlineColor(Color(0, 0, 0, 255));
  return rect;
}

void TextBox::resize(float _width, float _height) {
  vec2f vec;
  vec.x = MAX(_width, text->getWidth());
  vec.y = MAX(_height, text->getHeight());
  width = vec.x;
  height = vec.y;
  vec.x += 2 * padding;
  vec.y += 2 * padding;
  rect->setSize(vec);
  setCenter(vec.x / 2, vec.y / 2);
  text->setPosition(vec.x / 2, vec.y / 2);
}

void TextBox::draw(sf::RenderTarget* win) const {
  DrawObject::draw(win);
  text->draw(win);
}

void TextBox::setOutlineSize(float size) {
  outlineSize = MAX(size, 0);
  rect->setOutlineThickness(outlineSize);
}

void TextBox::setPadding(float x) {
  padding = MAX(x, 0);
  resize(width, height);
}

void TextBox::setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b) {
  rect->setFillColor(Color(r, g, b, 100));
  rect->setOutlineColor(Color(r, g, b, 255));
}

void TextBox::setFillColor(sf::Color color) {
  rect->setFillColor(color);
}
void TextBox::setOutlineColor(sf::Color color) {
  rect->setOutlineColor(color);
}

bool TextBox::isInBox(vec2f _pos) const {
  // note, doesn't take scaling into account, so far it's not needed
  vec2f pos = getAbsolutePosition() - center;
  vec2f pos2 = pos;
  pos2.x += getWidth();
  pos2.y += getHeight();
  return (
      _pos.x >= pos.x && _pos.y >= pos.y && _pos.x <= pos2.x &&
      _pos.y <= pos2.y);
}

bool TextBox::isInBox(vec2i _pos) const {
  return isInBox(vec2f{(float) _pos.x, (float) _pos.y});
}