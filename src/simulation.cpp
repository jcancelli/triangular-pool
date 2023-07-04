#include "simulation.hpp"

#include <cassert>
#include <glm/geometric.hpp>
#include <random>
#include <stdexcept>

#include "intersection.hpp"

Simulation::Simulation(float r1, float r2, float l, float meanY, float devY, float meanTheta,
                       float devTheta)
    : m_WallHigh(r1, r2, l),
      m_WallLow(-r1, -r2, l),
      m_Particle(),
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
  newIteration();
}

void Simulation::newIteration() {
  const float r1 = getR1();

  float initialY = m_ParticleYDistribution(m_RandomEngine);
  // if initialY is out of bounds re-calculate initialY (max 20 tries)
  for (int i = 0; (initialY < -r1 || initialY > r1) && i < 20; i++) {
    initialY = m_ParticleYDistribution(m_RandomEngine);
  }
  if (initialY < -r1 || initialY > r1) {
    throw std::runtime_error("Initial particle y out of valid range");
  }

  float initialTheta = m_ThetaDistribution(m_RandomEngine);
  // if theta is out of bounds re-calculate theta (max 20 tries)
  for (int i = 0; (initialTheta < M_PI_2 || initialTheta > -M_PI_2) && i < 20; i++) {
    initialTheta = m_ThetaDistribution(m_RandomEngine);
  }
  if (initialTheta < M_PI_2 || initialTheta > -M_PI_2) {
    throw std::runtime_error("Initial particle theta out of valid range");
  }

  m_Particle.setPosition(glm::vec2(0, initialY));
  m_Particle.setTheta(initialTheta);
  m_Particle.setSpeed(getL() / 10);
}

void Simulation::update(double deltaMs) {
}

void Simulation::immediate() {
  const float l = getL();
  const Segment finishLine(m_WallHigh.getB(), m_WallLow.getB());

  while (m_Particle.getPosition().x != l) {
    auto collisionPointOpt = nextCollision();

    if (collisionPointOpt.has_value()) {
      const glm::vec2 collisionPoint = collisionPointOpt.value();
      glm::vec2 wallNormal;
      if (collisionPoint.y > 0) {
        auto wallNormals = m_WallHigh.getNormals();
        // get the normal that is pointing toward the x axis
        wallNormal = wallNormals.first.y < 0 ? wallNormals.first : wallNormals.second;
      } else {
        auto wallNormals = m_WallLow.getNormals();
        // get the normal that is pointing toward the x axis
        wallNormal = wallNormals.first.y > 0 ? wallNormals.first : wallNormals.second;
      }
      m_Particle.setPosition(collisionPoint);
      m_Particle.reflect(wallNormal);
    } else {
      auto finalPositionOpt = intersection(m_Particle.getRay(), finishLine);
      assert(finalPositionOpt.has_value());
      m_Particle.setPosition(finalPositionOpt.value());
    }
  }
}

void Simulation::setR1(float r1) {
  if (r1 <= 0) {
    throw std::invalid_argument("Invalid r1 value");
  }
  m_WallHigh.setA(glm::vec2(0, r1));
  m_WallLow.setA(glm::vec2(0, -r1));
  newIteration();  // the simulation is resetted
}

float Simulation::getR1() const {
  return m_WallHigh.getA().y;
}

void Simulation::setR2(float r2) {
  if (r2 <= 0) {
    throw std::invalid_argument("Invalid r2 value");
  }
  const float l = getL();
  m_WallHigh.setB(glm::vec2(l, r2));
  m_WallLow.setB(glm::vec2(l, -r2));
  updateFinishLine();
  newIteration();  // the simulation is resetted
}

float Simulation::getR2() const {
  return m_WallHigh.getB().y;
}

void Simulation::setL(float l) {
  if (l <= 0) {
    throw std::invalid_argument("Invalid l value");
  }
  const float r2 = getR2();
  m_WallHigh.setB(glm::vec2(l, r2));
  m_WallLow.setB(glm::vec2(l, -r2));
  updateFinishLine();
  newIteration();  // the simulation is resetted
}

float Simulation::getL() const {
  return m_WallHigh.getB().x;
}

void Simulation::setMeanInitialParticleY(float meanY) {
  if (meanY > getR1() || meanY < -getR1()) {
    throw std::invalid_argument("Invalid meanY value");
  }
  m_ParticleYDistribution = std::normal_distribution(meanY, m_ParticleYDistribution.stddev());
}

float Simulation::getMeanInitialParticleY() const {
  return m_ParticleYDistribution.mean();
}

void Simulation::setInitialParticleYStdDev(float devY) {
  if (devY < 0) {
    throw std::invalid_argument("Invalid devY value");
  }
  m_ParticleYDistribution = std::normal_distribution(m_ParticleYDistribution.mean(), devY);
}

float Simulation::getInitialParticleYStdDev() const {
  return m_ParticleYDistribution.stddev();
}

void Simulation::setMeanInitialParticleTheta(float meanTheta) {
  if (meanTheta > M_PI_2 || meanTheta < -M_PI_2) {
    throw std::invalid_argument("Invalid meanTheta value");
  }
  m_ThetaDistribution = std::normal_distribution(meanTheta, m_ThetaDistribution.stddev());
}

float Simulation::getMeanInitialParticleTheta() const {
  return m_ThetaDistribution.mean();
}

void Simulation::setInitialParticleThetaStdDev(float devTheta) {
  if (devTheta < 0) {
    throw std::invalid_argument("Invalid devTheta value");
  }
  m_ThetaDistribution = std::normal_distribution(m_ThetaDistribution.mean(), devTheta);
}

float Simulation::getInitialParticleThetaStdDev() const {
  return m_ThetaDistribution.stddev();
}

void Simulation::updateFinishLine() {
  m_FinishLine.setA(m_WallHigh.getB());
  m_FinishLine.setB(m_WallLow.getB());
}

std::optional<glm::vec2> Simulation::nextCollision() const {
  Ray particleRay = m_Particle.getRay();

  if (m_Particle.getTheta() > 0) {
    return intersection(particleRay, m_WallHigh);
  }
  return intersection(particleRay, m_WallLow);
}
