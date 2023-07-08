#include "particle.hpp"

#include <sstream>

#include "../math/angles.hpp"
#include "../util/unused.hpp"

namespace pool {

namespace graphics {

static const double POINT_RADIUS = 5;

ParticleGraphics::ParticleGraphics(Particle const& particle) : m_Particle(particle) {
  m_VelocityLine.setOrigin(0, 1.25);
  m_VelocityLine.setSize(sf::Vector2f(40, 2.5));
  m_VelocityLine.setFillColor(sf::Color::Green);
  m_Point.setRadius(POINT_RADIUS);
  m_Point.setFontSize(11);
  m_Point.setTextSide(PointGraphics::TextSide::TopLeft);
  updatePosition();
  updateText();
  updateVelocityLine();
}

void ParticleGraphics::update(sf::Time const& delta) {
  UNUSED(delta);
  updatePosition();
  updateText();
  updateVelocityLine();
}

void ParticleGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_VelocityLine, states);
  target.draw(m_Point, states);
}

void ParticleGraphics::updatePosition() {
  auto pos = m_Particle.getPosition();
  m_Point.setPosition(pos.x * getCoordsScaling(), -pos.y * getCoordsScaling());
}

void ParticleGraphics::updateText() {
  std::ostringstream out;
  out.precision(2);
  auto pos = m_Particle.getPosition();
  out << std::fixed << "x: " << pos.x << ", y: " << pos.y
      << ", theta: " << math::degrees(m_Particle.getTheta()) << "deg";
  m_Point.setText(std::move(out).str());
}

void ParticleGraphics::updateVelocityLine() {
  auto theta = m_Particle.getTheta();
  auto pos = m_Particle.getPosition();
  m_VelocityLine.setRotation(math::degrees(-theta));
  m_VelocityLine.setPosition(pos.x * getCoordsScaling(), -pos.y * getCoordsScaling());
}

}  // namespace graphics

}  // namespace pool