#include "wall.hpp"

#include <glm/geometric.hpp>
#include <sstream>

#include "../math/angles.hpp"

static const double LINE_THICKNESS = 5;
static const double POINT_RADIUS = 4;

WallGraphics::WallGraphics(Wall const& wall) : m_Wall{wall} {
  const glm::vec2 wallDirection = glm::normalize(m_Wall.getB() - m_Wall.getA());
  const double wallAngle = std::atan2(-wallDirection.y, wallDirection.x);  // invert y

  m_Line.setOrigin(0, LINE_THICKNESS / 2);
  m_Line.setRotation(degrees(wallAngle));
  m_Line.setFillColor(sf::Color::Blue);

  m_PointA.setRadius(POINT_RADIUS);
  m_PointA.setFontSize(12);
  m_PointB.setRadius(POINT_RADIUS);
  m_PointB.setFontSize(12);

  m_PointA.setTextSide(PointGraphics::TextSide::Top);
  m_PointB.setTextSide(PointGraphics::TextSide::Top);
}

void WallGraphics::update(sf::Time const& delta) {
  m_Line.setSize(sf::Vector2f(m_Wall.length() * getCoordsScaling(), LINE_THICKNESS));
  updatePositions();
  updateText();
}

void WallGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_Line, states);
  target.draw(m_PointA, states);
  target.draw(m_PointB, states);
}

void WallGraphics::updatePositions() {
  m_Line.setPosition(m_Wall.getA().x * getCoordsScaling(), -m_Wall.getA().y * getCoordsScaling());
  m_PointA.setPosition(m_Wall.getA().x * getCoordsScaling(), -m_Wall.getA().y * getCoordsScaling());
  m_PointB.setPosition(m_Wall.getB().x * getCoordsScaling(), -m_Wall.getB().y * getCoordsScaling());
}

void WallGraphics::updateText() {
  const auto a = m_Wall.getA();
  const auto b = m_Wall.getB();
  std::ostringstream out;
  out.precision(2);
  out << std::fixed << "x: " << a.x << ", y: " << a.y;
  m_PointA.setText(std::move(out).str());
  out.str(std::string());  // clear buffer
  out << std::fixed << "x: " << b.x << ", y: " << b.y;
  m_PointB.setText(std::move(out).str());
}