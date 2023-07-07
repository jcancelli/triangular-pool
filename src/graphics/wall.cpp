#include "wall.hpp"

#include <glm/geometric.hpp>
#include <sstream>

#include "../math/angles.hpp"

static const double LINE_THICKNESS = 5;
static const double POINT_RADIUS = 4;

WallGraphics::WallGraphics(Wall const& wall) : m_Wall{wall}, m_CoordinatesScaling{1.0} {
  const glm::vec2 wallDirection = glm::normalize(m_Wall.getB() - m_Wall.getA());
  const double wallAngle = std::atan2(-wallDirection.y, wallDirection.x);  // invert y

  m_Line.setOrigin(0, LINE_THICKNESS / 2);
  m_Line.setRotation(degrees(wallAngle));
  m_Line.setFillColor(sf::Color::Blue);

  m_Line.setSize(sf::Vector2f(m_Wall.length() * m_CoordinatesScaling, LINE_THICKNESS));
  m_Line.setPosition(m_Wall.getA().x * m_CoordinatesScaling,
                     -m_Wall.getA().y * m_CoordinatesScaling);  // invert y

  m_PointA.setRadius(POINT_RADIUS);
  m_PointA.setFontSize(12);
  m_PointA.setPosition(m_Wall.getA().x * m_CoordinatesScaling,
                       -m_Wall.getA().y * m_CoordinatesScaling);  // invert y
  m_PointB.setRadius(POINT_RADIUS);
  m_PointB.setFontSize(12);
  m_PointB.setPosition(m_Wall.getB().x * m_CoordinatesScaling,
                       -m_Wall.getB().y * m_CoordinatesScaling);  // invert y

  m_PointA.setTextSide(PointGraphics::TextSide::Top);
  m_PointB.setTextSide(PointGraphics::TextSide::Top);

  updatePointsText();
}

void WallGraphics::update(double deltaTimeMs) {
  // no op
}

void WallGraphics::setCoordinatesScaling(double factor) {
  m_CoordinatesScaling = factor;
  m_Line.setSize(sf::Vector2f(m_Wall.length() * m_CoordinatesScaling, LINE_THICKNESS));
  m_Line.setPosition(m_Wall.getA().x * factor,
                     -m_Wall.getA().y * factor);    // invert y
  m_PointA.setPosition(m_Wall.getA().x * factor,
                       -m_Wall.getA().y * factor);  // invert y
  m_PointB.setPosition(m_Wall.getB().x * factor,
                       -m_Wall.getB().y * factor);  // invert y
}

double WallGraphics::getCoordinatesScaling() const {
  return m_CoordinatesScaling;
}

void WallGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_Line, states);
  target.draw(m_PointA, states);
  target.draw(m_PointB, states);
}

void WallGraphics::updatePointsText() {
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