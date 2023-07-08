#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <optional>
#include <random>

#include "particle.hpp"
#include "statistics.hpp"
#include "util/listeners.hpp"
#include "wall.hpp"

class Simulation {
 private:
  Wall m_WallHigh, m_WallLow;
  Particle m_Particle;
  Segment m_StartLine, m_FinishLine;
  std::default_random_engine m_RandomEngine;
  std::normal_distribution<float> m_ParticleYDistribution;
  std::normal_distribution<float> m_ThetaDistribution;
  Statistics m_Stats;
  Listeners<Particle const&> m_NewIterationListeners;
  Listeners<Particle const&> m_CollisionListeners;
  Listeners<Particle const&> m_IterationEndedListeners;

 public:
  Simulation(float r1, float r2, float l, float meanY, float devY, float meanTheta, float devTheta);

  void newIteration();          // Start a new simulation
  void update(double deltaMs);  // Progress the simulation by delta time
  void immediate();             // End the simulation in one go
  float getR1() const;
  float getR2() const;
  float getL() const;
  float getMeanInitialParticleY() const;
  float getInitialParticleYStdDev() const;
  float getMeanInitialParticleTheta() const;
  float getInitialParticleThetaStdDev() const;
  Particle const& getParticle() const;
  Wall const& getWallHigh() const;
  Wall const& getWallLow() const;
  Statistics const& getStats() const;
  void setVerboseOutput(bool verbose);
  bool isVerboseOutput() const;
  unsigned addNewIterationListener(Listeners<Particle const&>::Listener listener);
  void removeNewIterationListener(unsigned listenerID);
  unsigned addCollisionListener(Listeners<Particle const&>::Listener listener);
  void removeCollisionListener(unsigned listenerID);
  unsigned addIterationEndedListener(Listeners<Particle const&>::Listener listener);
  void removeIterationEndedListener(unsigned listenerID);

 private:
  struct Collision {
    glm::vec2 position;
    glm::vec2 wallNormal;
  };

 private:
  std::optional<Collision> nextCollision() const;
  glm::vec2 wallNormalFromCollisionPoint(glm::vec2 const& collisionPoint) const;
};

#endif