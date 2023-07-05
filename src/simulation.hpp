#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <optional>
#include <random>

#include "particle.hpp"
#include "wall.hpp"

class Simulation {
 private:
  Wall m_WallHigh, m_WallLow;
  Particle m_Particle;
  Segment m_FinishLine;
  std::default_random_engine m_RandomEngine;
  std::normal_distribution<float> m_ParticleYDistribution;
  std::normal_distribution<float> m_ThetaDistribution;

 public:
  Simulation(float r1, float r2, float l, float meanY, float devY, float meanTheta, float devTheta);

  void newIteration();          // Start a new simulation
  void update(double deltaMs);  // Progress the simulation by delta time
  void immediate();             // End the simulation in one go
  void setR1(float r1);
  float getR1() const;
  void setR2(float r2);
  float getR2() const;
  void setL(float l);
  float getL() const;
  void setMeanInitialParticleY(float meanY);
  float getMeanInitialParticleY() const;
  void setInitialParticleYStdDev(float devY);
  float getInitialParticleYStdDev() const;
  void setMeanInitialParticleTheta(float meanTheta);
  float getMeanInitialParticleTheta() const;
  void setInitialParticleThetaStdDev(float devTheta);
  float getInitialParticleThetaStdDev() const;
  Particle getParticle() const;

 private:
  void updateFinishLine();
  std::optional<glm::vec2> nextCollision() const;
};

#endif