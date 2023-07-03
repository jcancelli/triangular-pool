#include "ray.hpp"

#include <glm/geometric.hpp>

Ray::Ray(glm::vec2 const& origin, glm::vec2 const& direction)
    : m_Origin(origin), m_Direction(glm::normalize(direction)) {
}

Ray::Ray(glm::vec2 const& direction) : m_Origin(0, 0), m_Direction(glm::normalize(direction)) {
}

Ray::Ray(Ray const& other) : m_Origin(other.m_Origin), m_Direction(other.m_Direction) {
}

void Ray::setOrigin(glm::vec2 const& origin) {
  m_Origin = origin;
}

glm::vec2 Ray::getOrigin() const {
  return m_Origin;
}

void Ray::setDirection(glm::vec2 const& direction) {
  m_Direction = glm::normalize(direction);
}

glm::vec2 Ray::getDirection() const {
  return m_Direction;
}
