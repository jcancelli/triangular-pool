#include "particle.hpp"

#include <cmath>
#include <glm/geometric.hpp>
#include <stdexcept>

#include "math/angles.hpp"

Particle::Particle() : m_Position(0, 0), m_Velocity(0, 0) {
}

Particle::Particle(double y, double speed, double theta)
    : m_Position(0, y), m_Velocity(std::cos(theta) * speed, std::sin(theta) * speed) {
}

Particle::Particle(Particle const& other)
    : m_Position(other.m_Position), m_Velocity(other.m_Velocity) {
}

void Particle::setPosition(glm::vec2 const& position) {
  m_Position = position;
}

glm::vec2 Particle::getPosition() const {
  return m_Position;
}

void Particle::setVelocity(glm::vec2 const& velocity) {
  m_Velocity = velocity;
}

glm::vec2 Particle::getVelocity() const {
  return m_Velocity;
}

void Particle::setSpeed(float speed) {
  if (speed < 0) {
    throw std::invalid_argument("Particle speed cannot be negative");
  }
  m_Velocity = glm::normalize(m_Velocity) * speed;
}

float Particle::getSpeed() const {
  return glm::length(m_Velocity);
}

void Particle::setTheta(float theta) {
  const float speed = m_Velocity.length();
  m_Velocity = glm::vec2(std::cos(theta) * speed, std::sin(theta) * speed);
}

float Particle::getTheta() const {
  return std::atan2(m_Velocity.y, m_Velocity.x);
}

Ray Particle::getRay() const {
  return Ray(m_Position, m_Velocity);
}

void Particle::reflect(glm::vec2 const& surfaceNormal) {
  m_Velocity = glm::reflect(m_Velocity, glm::normalize(surfaceNormal));
}

std::ostream& operator<<(std::ostream& os, Particle const& particle) {
  return os << "Position: " << particle.m_Position << ", Velocity: " << particle.m_Velocity
            << ", Theta: " << degrees(particle.getTheta());
}