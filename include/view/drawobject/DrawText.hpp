#ifndef VIEW_DRAWTEXT_HPP
#define VIEW_DRAWTEXT_HPP

#include "view/drawobject/DrawObject.hpp"

class DrawText : public DrawObject {
 private:
  static sf::Font font;
  static sf::Text* createText(
      std::string text, sf::Color color = sf::Color::Black);
  sf::Text* textObject;

  DrawText(sf::Text* obj);

 public:
  DrawText(std::string txt, sf::Color color);
  DrawText(std::string text);
  ~DrawText();

  void setText(char* text);
  void setText(std::string text);
};

#endif
