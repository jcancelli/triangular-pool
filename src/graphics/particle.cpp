#include "particle.hpp"

#include <iostream>
#include <sstream>

#include "../math/angles.hpp"

static const double VELOCITY_LINE_THICKNESS = 2.5;
static const double POINT_RADIUS = 5;

ParticleGraphics::ParticleGraphics(Particle const& particle)
    : m_Particle(particle), m_CoordinatesScalingFactor{1.0} {
  m_VelocityLine.setOrigin(0, VELOCITY_LINE_THICKNESS / 2);
  m_VelocityLine.setFillColor(sf::Color::Green);
  m_Point.setRadius(POINT_RADIUS);
  m_Point.setFontSize(11);
  m_Point.setTextSide(PointGraphics::TextSide::TopLeft);
  updatePosition();
  updateText();
  updateVelocityLine();
}

void ParticleGraphics::update(double deltaTimeMs) {
  updatePosition();
  updateText();
  updateVelocityLine();
}

void ParticleGraphics::setCoordinatesScaling(double factor) {
  m_CoordinatesScalingFactor = factor;
}

double ParticleGraphics::getCoordinatesScaling() const {
  return m_CoordinatesScalingFactor;
}

void ParticleGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_VelocityLine, states);
  target.draw(m_Point, states);
}

void ParticleGraphics::updatePosition() {
  auto pos = m_Particle.getPosition();
  m_Point.setPosition(pos.x * m_CoordinatesScalingFactor, pos.y * m_CoordinatesScalingFactor);
}

void ParticleGraphics::updateText() {
  std::ostringstream out;
  out.precision(2);
  auto pos = m_Particle.getPosition();
  out << std::fixed << "x: " << pos.x << ", y: " << pos.y
      << ", theta: " << degrees(m_Particle.getTheta()) << "deg";
  m_Point.setText(std::move(out).str());
}

void ParticleGraphics::updateVelocityLine() {
  auto theta = m_Particle.getTheta();
  auto pos = m_Particle.getPosition();
  m_VelocityLine.setSize(
      sf::Vector2f(m_Particle.getSpeed() * m_CoordinatesScalingFactor, VELOCITY_LINE_THICKNESS));
  m_VelocityLine.setRotation(degrees(theta));
  m_VelocityLine.setPosition(pos.x * m_CoordinatesScalingFactor,
                             pos.y * m_CoordinatesScalingFactor);
}
