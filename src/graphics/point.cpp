#include "point.hpp"

#include "font.hpp"

static const unsigned DEFAULT_RADIUS = 5;
static const unsigned DEFAULT_FONT_SIZE = 16;
static const sf::Color DEFAULT_COLOR = sf::Color::Red;

PointGraphics::PointGraphics() {
  setRadius(DEFAULT_RADIUS);

  m_Text.setFont(g_FontLucindaSansRegular);
  setText("");
  setFontSize(DEFAULT_FONT_SIZE);

  setColor(DEFAULT_COLOR);
}

PointGraphics::PointGraphics(double x, double y, double radius, std::string const& text) {
  setRadius(radius);

  m_Text.setFont(g_FontLucindaSansRegular);
  setText(text);
  setFontSize(DEFAULT_FONT_SIZE);

  setPosition(x, y);
  setColor(DEFAULT_COLOR);
}

void PointGraphics::setText(std::string const& text) {
  m_Text.setString(text);
}

std::string PointGraphics::getText() const {
  return m_Text.getString();
}

void PointGraphics::setColor(sf::Color const& color) {
  m_Point.setFillColor(color);
  m_Text.setFillColor(color);
}

sf::Color PointGraphics::getColor() const {
  return m_Point.getFillColor();
}

void PointGraphics::setFontSize(unsigned fontSize) {
  m_Text.setCharacterSize(fontSize);
  alignText();
}

unsigned PointGraphics::getFontSize() const {
  return m_Text.getCharacterSize();
}

void PointGraphics::setRadius(double radius) {
  m_Point.setRadius(radius);
  m_Point.setOrigin(radius, radius);
  alignText();
}

double PointGraphics::getRadius() const {
  return m_Point.getRadius();
}

void PointGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_Point, states);
  target.draw(m_Text, states);
}

void PointGraphics::alignText() {
  auto radius = getRadius();
  m_Text.setPosition(radius * 2, -radius - getFontSize());
}
