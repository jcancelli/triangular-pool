#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <glm/vec2.hpp>
#include <ostream>

#include "math/ray.hpp"

namespace pool {

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
  math::Ray getRay() const;
  void reflect(glm::vec2 const& surfaceNormal);
  friend std::ostream& operator<<(std::ostream& os, Particle const& particle);
};

}  // namespace pool

#endif