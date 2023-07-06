#ifndef GRAPHICS_POINT_HPP
#define GRAPHICS_POINT_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "graphics.hpp"

class PointGraphics : public Graphics {
 public:
  enum class TextSide { Top, TopRight, Right, BottomRight, Bottom, BottomLeft, Left, TopLeft };

 private:
  sf::CircleShape m_Point;
  sf::Text m_Text;
  TextSide m_TextSide;

 public:
  PointGraphics();
  PointGraphics(double x, double y, double radius = 5.0, std::string const& text = "");

  void setText(std::string const& text);
  std::string getText() const;
  void setTextSide(TextSide side);
  TextSide getTextSide() const;
  void setColor(sf::Color const& color);
  sf::Color getColor() const;
  void setFontSize(unsigned fontSize);
  unsigned getFontSize() const;
  void setRadius(double radius);
  double getRadius() const;

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  void alignText();
};

#endif