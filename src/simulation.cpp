#include "simulation.hpp"

#include <cassert>
#include <glm/geometric.hpp>
#include <random>
#include <stdexcept>

#include "math/intersection.hpp"

Simulation::Simulation(float r1, float r2, float l, float meanY, float devY, float meanTheta,
                       float devTheta)
    : m_WallHigh(r1, r2, l),
      m_WallLow(-r1, -r2, l),
      m_Particle(),
      m_StartLine(m_WallHigh.getA(), m_WallLow.getA()),
      m_FinishLine(m_WallHigh.getB(), m_WallLow.getB()),
      m_ParticleYDistribution(meanY, devY),
      m_ThetaDistribution(meanTheta, devTheta) {
  if (meanY > r1 || meanY < -r1) {
    throw std::invalid_argument("Invalid meanY value");
  }
  if (meanTheta > M_PI_2 || meanTheta < -M_PI_2) {
    throw std::invalid_argument("Invalid meanTheta value");
  }
  if (devY < 0) {
    throw std::invalid_argument("Invalid devY value");
  }
  if (devTheta < 0) {
    throw std::invalid_argument("Invalid devTheta value");
  }

  addNewIterationListener([this](Particle const& particle) {
    this->m_Stats.createNewEntry(particle.getPosition(), particle.getTheta());
  });
  addCollisionListener([this](Particle const& particle) {  //
    this->m_Stats.addCollision(particle.getPosition());    //
  });                                                      //
  addIterationEndedListener([this](Particle const& particle) {
    this->m_Stats.commitEntry(particle.getPosition(), particle.getTheta());
  });

  newIteration();
}

void Simulation::newIteration() {
  const float r1 = getR1();

  float initialY = m_ParticleYDistribution(m_RandomEngine);
  // if initialY is out of bounds re-calculate initialY (max 20 tries)
  for (int i = 0; (initialY <= -r1 || initialY >= r1) && i < 20; i++) {
    initialY = m_ParticleYDistribution(m_RandomEngine);
  }
  if (initialY <= -r1 || initialY >= r1) {
    throw std::runtime_error("Initial particle y out of valid range");
  }

  float initialTheta = m_ThetaDistribution(m_RandomEngine);
  // if theta is out of bounds re-calculate theta (max 20 tries)
  for (int i = 0; (initialTheta > M_PI_2 || initialTheta < -M_PI_2) && i < 20; i++) {
    initialTheta = m_ThetaDistribution(m_RandomEngine);
  }
  if (initialTheta > M_PI_2 || initialTheta < -M_PI_2) {
    throw std::runtime_error("Initial particle theta out of valid range");
  }

  m_Particle.setPosition(glm::vec2(0, initialY));
  m_Particle.setTheta(initialTheta);
  m_Particle.setSpeed(getL() / 10);

  m_NewIterationListeners.notify(m_Particle);
}

void Simulation::update(double deltaMs) {
  // TODO: Implement update
}

void Simulation::immediate() {
  const float l = getL();

  while (m_Particle.getPosition().x != l) {
    auto collisionPointOpt = nextCollision();

    if (collisionPointOpt.has_value()) {
      const glm::vec2 collisionPoint = collisionPointOpt.value();
      glm::vec2 wallNormal;
      if (collisionPoint.y > 0) {
        auto wallNormals = m_WallHigh.getNormals();
        // Get the normal that is pointing toward the x axis
        wallNormal = wallNormals.first.y < 0 ? wallNormals.first : wallNormals.second;
      } else {
        auto wallNormals = m_WallLow.getNormals();
        // Get the normal that is pointing toward the x axis
        wallNormal = wallNormals.first.y > 0 ? wallNormals.first : wallNormals.second;
      }
      m_Particle.setPosition(collisionPoint);
      m_Particle.reflect(wallNormal);
      m_CollisionListeners.notify(m_Particle);
    } else {                                // Check if particle reached final position
      auto finalPositionOpt = intersection(m_Particle.getRay(), m_FinishLine);
      if (!finalPositionOpt.has_value()) {  // Check if particle came out of the back
        finalPositionOpt = intersection(m_Particle.getRay(), m_StartLine);
        assert(finalPositionOpt.has_value());
      }
      m_Particle.setPosition(finalPositionOpt.value());
      m_IterationEndedListeners.notify(m_Particle);
    }
  }
}

float Simulation::getR1() const {
  return m_WallHigh.getA().y;
}

float Simulation::getR2() const {
  return m_WallHigh.getB().y;
}

float Simulation::getL() const {
  return m_WallHigh.getB().x;
}

float Simulation::getMeanInitialParticleY() const {
  return m_ParticleYDistribution.mean();
}

float Simulation::getInitialParticleYStdDev() const {
  return m_ParticleYDistribution.stddev();
}

float Simulation::getMeanInitialParticleTheta() const {
  return m_ThetaDistribution.mean();
}

float Simulation::getInitialParticleThetaStdDev() const {
  return m_ThetaDistribution.stddev();
}

Particle const& Simulation::getParticle() const {
  return m_Particle;
}

Wall const& Simulation::getWallHigh() const {
  return m_WallHigh;
}

Wall const& Simulation::getWallLow() const {
  return m_WallLow;
}

Statistics Simulation::getStats() const {
  return m_Stats;
}

unsigned Simulation::addNewIterationListener(Listeners<Particle const&>::Listener listener) {
  return m_NewIterationListeners.add(listener);
}

void Simulation::removeNewIterationListener(unsigned listenerID) {
  m_NewIterationListeners.remove(listenerID);
}

unsigned Simulation::addCollisionListener(Listeners<Particle const&>::Listener listener) {
  return m_CollisionListeners.add(listener);
}

void Simulation::removeCollisionListener(unsigned listenerID) {
  m_CollisionListeners.remove(listenerID);
}

unsigned Simulation::addIterationEndedListener(Listeners<Particle const&>::Listener listener) {
  return m_IterationEndedListeners.add(listener);
}

void Simulation::removeIterationEndedListener(unsigned listenerID) {
  m_IterationEndedListeners.remove(listenerID);
}

std::optional<glm::vec2> Simulation::nextCollision() const {
  Ray particleRay = m_Particle.getRay();

  if (m_Particle.getTheta() > 0) {
    return intersection(particleRay, m_WallHigh);
  }
  return intersection(particleRay, m_WallLow);
}
