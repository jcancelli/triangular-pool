#include "simulation.hpp"

namespace pool {

namespace graphics {

SimulationGraphics::SimulationGraphics(Simulation& simulation)
    : m_Simulation{simulation},
      m_UpperWallGraphics(simulation.getWallHigh()),
      m_LowerWallGraphics(simulation.getWallLow()),
      m_ParticleGraphics(simulation.getParticle()) {
  m_Simulation.addCollisionListener([this](Particle const& particle) {
    auto pos = particle.getPosition();
    PointGraphics collisionGraphics;
    collisionGraphics.setColor(sf::Color(0xe25825ff));
    collisionGraphics.setRadius(4);
    collisionGraphics.setPosition(pos.x * this->getCoordsScaling(),
                                  -pos.y * this->getCoordsScaling());
    this->m_CollisionPointsGraphics.push_back(collisionGraphics);
  });
  m_Simulation.addIterationEndedListener([this](Particle const& particle) {
    this->m_CollisionPointsGraphics.clear();
    auto pos = particle.getPosition();
    PointGraphics finalPosGraphics;
    finalPosGraphics.setColor(sf::Color::Cyan);
    finalPosGraphics.setRadius(2);
    finalPosGraphics.setPosition(pos.x * this->getCoordsScaling(),
                                 -pos.y * this->getCoordsScaling());
    this->m_FinalPositionsPointsGraphics.push_back(finalPosGraphics);
  });
}

void SimulationGraphics::update(sf::Time const& delta) {
  m_UpperWallGraphics.setCoordsScaling(getCoordsScaling());
  m_LowerWallGraphics.setCoordsScaling(getCoordsScaling());
  m_ParticleGraphics.setCoordsScaling(getCoordsScaling());
  m_UpperWallGraphics.update(delta);
  m_LowerWallGraphics.update(delta);
  m_ParticleGraphics.update(delta);
  for (auto& collisionGraphics : m_CollisionPointsGraphics) {
    collisionGraphics.setCoordsScaling(getCoordsScaling());
    collisionGraphics.update(delta);
  }
  for (auto& finalPositionGraphics : m_FinalPositionsPointsGraphics) {
    finalPositionGraphics.setCoordsScaling(getCoordsScaling());
    finalPositionGraphics.update(delta);
  }
}

void SimulationGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_UpperWallGraphics, states);
  target.draw(m_LowerWallGraphics, states);
  for (auto const& collisionGraphics : m_CollisionPointsGraphics) {
    target.draw(collisionGraphics, states);
  }
  for (auto const& finalPositionGraphics : m_FinalPositionsPointsGraphics) {
    target.draw(finalPositionGraphics, states);
  }
  target.draw(m_ParticleGraphics, states);
}

}  // namespace graphics

}  // namespace pool