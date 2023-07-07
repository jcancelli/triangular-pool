#include "simulation.hpp"

SimulationGraphics::SimulationGraphics(Simulation const& simulation)
    : m_Simulation{simulation},
      m_UpperWallGraphics(simulation.getWallHigh()),
      m_LowerWallGraphics(simulation.getWallLow()),
      m_ParticleGraphics(simulation.getParticle()),
      m_CoordinatesScaling{1.0} {
}

void SimulationGraphics::update(double deltaTimeMs) {
  m_UpperWallGraphics.update(deltaTimeMs);
  m_LowerWallGraphics.update(deltaTimeMs);
  m_ParticleGraphics.update(deltaTimeMs);
}

void SimulationGraphics::setCoordinatesScaling(double factor) {
  m_CoordinatesScaling = factor;
  m_UpperWallGraphics.setCoordinatesScaling(factor);
  m_LowerWallGraphics.setCoordinatesScaling(factor);
  m_ParticleGraphics.setCoordinatesScaling(factor);
}

double SimulationGraphics::getCoordinatesScaling() const {
  return m_CoordinatesScaling;
}

void SimulationGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_UpperWallGraphics, states);
  target.draw(m_LowerWallGraphics, states);
  target.draw(m_ParticleGraphics, states);
}