#ifndef VIEW_DRAWTEXT_HPP
#define VIEW_DRAWTEXT_HPP

#include "view/drawobject/DrawObject.hpp"

class DrawText : public DrawObject {
 private:
  static sf::Font font;
  static sf::Text* createText(std::string text, sf::Color color, int size);

  sf::Text* textObject;
  // float width;
  // float height;

  DrawText(sf::Text* obj);

 public:
  DrawText(std::string text, sf::Color color = sf::Color::Black, int size = 30);
  DrawText(std::string text, int size);
  DrawText(std::string text);
  ~DrawText();

  void setText(const char* text);
  void setText(std::string text);
};

#endif
