#ifndef VIEW_DRAWTEXT_HPP
#define VIEW_DRAWTEXT_HPP

#include "DrawObject.hpp"

//todo: rethink this, this is not very good
class DrawText : DrawObject {
private:
  sf::Font& font;
  sf::Text textObject;
  std::string str;
public:
  DrawText(sf::Font& font);
  ~DrawText();
};

#endif