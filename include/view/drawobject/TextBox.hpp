#ifndef VIEW_TEXTBOX_HPP
#define VIEW_TEXTBOX_HPP

#include "view/drawobject/DrawObject.hpp"
#include "view/drawobject/DrawText.hpp"

class TextBox : public DrawObject {
 private:
  sf::RectangleShape* rect;
  DrawText* text;
  float width;
  float height;
  float padding;
  float outlineSize;

  sf::RectangleShape* initRect();

 public:
  TextBox(
      const char* text,
      sf::Color fontColor = sf::Color::White,
      int fontSize = 30);

  virtual ~TextBox();

  void resize(float width, float height);
  virtual void draw(sf::RenderTarget* win) const;
  DrawText* getTextObject();
  float getWidth() const;
  float getHeight() const;

  void setOutlineSize(float size);
  void setPadding(float padding);
  void setBackgroundColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
};

#endif
