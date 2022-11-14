#include "view/DrawText.hpp"

DrawText::DrawText(sf::Font& _font): font{_font}, textObject{}, str{""} {}
DrawText::~DrawText() {}