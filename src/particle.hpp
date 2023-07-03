#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <glm/vec2.hpp>

#include "ray.hpp"

class Particle {
 private:
  glm::vec2 m_Position;
  glm::vec2 m_Velocity;

 public:
  Particle();
  Particle(double y, double speed, double theta);
  Particle(Particle const& other);

  void setPosition(glm::vec2 const& position);
  glm::vec2 getPosition() const;
  void setVelocity(glm::vec2 const& velocity);
  glm::vec2 getVelocity() const;
  void setSpeed(float speed);
  float getSpeed() const;
  void setTheta(float theta);
  float getTheta() const;
  Ray getRay() const;
};

#endif