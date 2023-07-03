#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <glm/vec2.hpp>

class Particle {
 private:
  static const double PARTICLE_SPEED;
  glm::vec2 m_Position;
  glm::vec2 m_Speed;

 public:
  Particle();
  Particle(double y);
  Particle(Particle const& other) {
    m_Spee
  }
};

#endif