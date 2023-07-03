#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <glm/vec2.hpp>

class Particle {
 private:
  glm::vec2 m_Position;
  glm::vec2 m_Velocity;

 public:
  Particle(double y, double speed, double theta);
  Particle(Particle const& other);

  void setPosition(glm::vec2 const& position);
  glm::vec2 getPosition() const;
  void setVelocity(glm::vec2 const& velocity);
  glm::vec2 getVelocity() const;
  double theta() const;
};

#endif