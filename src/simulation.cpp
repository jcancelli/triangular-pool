#include "simulation.hpp"

#include <cassert>
#include <glm/geometric.hpp>
#include <random>
#include <stdexcept>

#include "math/intersection.hpp"

namespace pool {

Simulation::Simulation(float r1, float r2, float l, float meanY, float devY, float meanTheta,
                       float devTheta)
    : m_WallHigh(r1, r2, l),
      m_WallLow(-r1, -r2, l),
      m_Particle(),
      m_StartLine(m_WallHigh.getA(), m_WallLow.getA()),
      m_FinishLine(m_WallHigh.getB(), m_WallLow.getB()),
      m_SpeedMultiplier{1.0},
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
  m_Particle.setSpeed(getL() / 2.2);

  m_NewIterationListeners.notify(m_Particle);
}

void Simulation::update(double deltaMs) {
  double distanceToTravel = m_Particle.getSpeed() * deltaMs / 1000.0 * m_SpeedMultiplier;

  while (distanceToTravel > 0.0) {
    auto nextCollisionOpt = nextCollision();
    if (nextCollisionOpt.has_value()) {  // Particle is pointing toward a wall
      auto nextCollisionV = nextCollisionOpt.value();
      auto distanceToNextCollision =
          glm::length(nextCollisionV.position - m_Particle.getPosition());
      if (distanceToTravel >= distanceToNextCollision) {  // Particle will hit the wall
        m_Particle.setPosition(nextCollisionV.position);
        m_Particle.reflect(nextCollisionV.wallNormal);
        m_CollisionListeners.notify(m_Particle);
        distanceToTravel -= distanceToNextCollision;
      } else {  // Particle won't hit the wall
        auto particleDirection = glm::normalize(m_Particle.getVelocity());
        auto nextPositionOffset = particleDirection * float(distanceToTravel);
        m_Particle.setPosition(m_Particle.getPosition() + nextPositionOffset);
        distanceToTravel = 0.0;
      }
    } else {  // Particle is pointing at either finish line or starting line
      auto particleRay = m_Particle.getRay();
      auto finalPositionOpt = intersection(particleRay, m_FinishLine);
      if (!finalPositionOpt.has_value()) {
        finalPositionOpt = intersection(particleRay, m_StartLine);
        assert(finalPositionOpt.has_value());
      }
      auto finalPosition = finalPositionOpt.value();
      auto distanceToFinalPosition = glm::length(finalPosition - m_Particle.getPosition());
      if (distanceToTravel >= distanceToFinalPosition) {  // Particle will reach final position
        m_Particle.setPosition(finalPosition);
        m_IterationEndedListeners.notify(m_Particle);
        distanceToTravel = 0.0;
      } else {  // Particle won't reach final position
        auto particleDirection = glm::normalize(m_Particle.getVelocity());
        auto nextPositionOffset = particleDirection * float(distanceToTravel);
        m_Particle.setPosition(m_Particle.getPosition() + nextPositionOffset);
        distanceToTravel = 0.0;
      }
    }
  }
}

void Simulation::immediate() {
  bool isFinished = false;

  while (!isFinished) {
    auto collisionOpt = nextCollision();

    if (collisionOpt.has_value()) {  // Particle will collide with wall
      auto collision = collisionOpt.value();
      m_Particle.setPosition(collision.position);
      m_Particle.reflect(collision.wallNormal);
      m_CollisionListeners.notify(m_Particle);
      continue;
    }

    // Particle will reach final position

    auto particleRay = m_Particle.getRay();
    auto finalPositionOpt = intersection(particleRay, m_FinishLine);
    if (!finalPositionOpt.has_value()) {  // Check if particle will come out of the back
      finalPositionOpt = intersection(particleRay, m_StartLine);
      assert(finalPositionOpt.has_value());
    }
    m_Particle.setPosition(finalPositionOpt.value());
    m_IterationEndedListeners.notify(m_Particle);
    isFinished = true;
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

math::Segment const& Simulation::getStartLine() const {
  return m_StartLine;
}

math::Segment const& Simulation::getFinishLine() const {
  return m_FinishLine;
}

Statistics const& Simulation::getStats() const {
  return m_Stats;
}

void Simulation::setSpeedMultiplier(float multiplier) {
  if (multiplier <= 0) {
    throw std::invalid_argument("Error: Speed multiplier must be positive");
  }
  m_SpeedMultiplier = multiplier;
}

float Simulation::getSpeedMultiplier() const {
  return m_SpeedMultiplier;
}

unsigned Simulation::addNewIterationListener(util::Listeners<Particle const&>::Listener listener) {
  return m_NewIterationListeners.add(listener);
}

void Simulation::removeNewIterationListener(unsigned listenerID) {
  m_NewIterationListeners.remove(listenerID);
}

unsigned Simulation::addCollisionListener(util::Listeners<Particle const&>::Listener listener) {
  return m_CollisionListeners.add(listener);
}

void Simulation::removeCollisionListener(unsigned listenerID) {
  m_CollisionListeners.remove(listenerID);
}

unsigned Simulation::addIterationEndedListener(
    util::Listeners<Particle const&>::Listener listener) {
  return m_IterationEndedListeners.add(listener);
}

void Simulation::removeIterationEndedListener(unsigned listenerID) {
  m_IterationEndedListeners.remove(listenerID);
}

std::optional<Simulation::Collision> Simulation::nextCollision() const {
  auto particleRay = m_Particle.getRay();
  auto& collidedWall = m_Particle.getTheta() > 0 ? m_WallHigh : m_WallLow;
  auto collisionPointOpt = math::intersection(particleRay, collidedWall);
  if (!collisionPointOpt.has_value()) {
    return {};
  }
  auto collisionPoint = collisionPointOpt.value();
  auto wallNormal = wallNormalFromCollisionPoint(collisionPoint);
  return Collision{.position = collisionPoint, .wallNormal = wallNormal};
}

glm::vec2 Simulation::wallNormalFromCollisionPoint(glm::vec2 const& collisionPoint) const {
  if (collisionPoint.y > 0) {
    auto wallNormals = m_WallHigh.getNormals();
    return wallNormals.first.y < 0 ? wallNormals.first : wallNormals.second;
  }
  auto wallNormals = m_WallLow.getNormals();
  return wallNormals.first.y > 0 ? wallNormals.first : wallNormals.second;
}

}  // namespace pool
