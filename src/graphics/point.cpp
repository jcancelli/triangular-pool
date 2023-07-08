#include "point.hpp"

#include "../util/unused.hpp"
#include "font.hpp"

namespace pool {

namespace graphics {

static const unsigned DEFAULT_RADIUS = 5;
static const unsigned DEFAULT_FONT_SIZE = 15;
static const sf::Color DEFAULT_COLOR = sf::Color::Red;
static const PointGraphics::TextSide DEFAULT_TEXT_SIDE = PointGraphics::TextSide::Top;

PointGraphics::PointGraphics() : m_TextSide(DEFAULT_TEXT_SIDE) {
  setRadius(DEFAULT_RADIUS);

  m_Text.setFont(g_FontLucindaSansRegular);
  setText("");
  setFontSize(DEFAULT_FONT_SIZE);

  setColor(DEFAULT_COLOR);
}

void PointGraphics::update(sf::Time const& delta) {
  UNUSED(delta);
  updateText();
}

void PointGraphics::setText(std::string const& text) {
  m_Text.setString(text);
  setTextSide(m_TextSide);
}

std::string PointGraphics::getText() const {
  return m_Text.getString();
}

void PointGraphics::setTextSide(PointGraphics::TextSide side) {
  m_TextSide = side;
}

PointGraphics::TextSide PointGraphics::getTextSide() const {
  return m_TextSide;
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
}

unsigned PointGraphics::getFontSize() const {
  return m_Text.getCharacterSize();
}

void PointGraphics::setRadius(double radius) {
  m_Point.setRadius(radius);
  m_Point.setOrigin(radius, radius);
}

double PointGraphics::getRadius() const {
  return m_Point.getRadius();
}

void PointGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_Point, states);
  target.draw(m_Text, states);
}

void PointGraphics::updateText() {
  auto radius = getRadius();
  const auto bounds = m_Text.getLocalBounds();
  const double margin = 5;
  switch (m_TextSide) {
    case TextSide::Top:
      m_Text.setPosition((-bounds.width / 2) + radius, -bounds.height - radius - margin);
      break;
    case TextSide::TopRight:
      m_Text.setPosition(radius * 2 + margin, -bounds.height - radius - margin);
      break;
    case TextSide::Right:
      m_Text.setPosition(radius * 2 + margin, radius);
      break;
    case TextSide::BottomRight:
      m_Text.setPosition(radius * 2 + margin, radius * 2 + margin);
      break;
    case TextSide::Bottom:
      m_Text.setPosition((-bounds.width / 2) + radius, radius * 2 + margin);
      break;
    case TextSide::BottomLeft:
      m_Text.setPosition(-bounds.width - radius - margin, radius * 2 + margin);
      break;
    case TextSide::Left:
      m_Text.setPosition(-bounds.width - radius - margin, radius);
      break;
    case TextSide::TopLeft:
      m_Text.setPosition(-bounds.width - radius - margin, -bounds.height - radius - margin);
      break;
  }
}

}  // namespace graphics

}  // namespace pool
