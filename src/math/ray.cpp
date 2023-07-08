#include "ray.hpp"

#include <glm/geometric.hpp>

namespace pool {

namespace math {

Ray::Ray(glm::vec2 const& origin, glm::vec2 const& direction)
    : m_Origin(origin), m_Direction(glm::normalize(direction)) {
  updateEquation();
}

Ray::Ray(glm::vec2 const& direction) : m_Origin(0, 0), m_Direction(glm::normalize(direction)) {
  updateEquation();
}

Ray::Ray(Ray const& other)
    : m_Origin(other.m_Origin),
      m_Direction(other.m_Direction),
      m_LineEquation(other.m_LineEquation) {
}

void Ray::setOrigin(glm::vec2 const& origin) {
  m_Origin = origin;
  updateEquation();
}

glm::vec2 Ray::getOrigin() const {
  return m_Origin;
}

void Ray::setDirection(glm::vec2 const& direction) {
  m_Direction = glm::normalize(direction);
  updateEquation();
}

glm::vec2 Ray::getDirection() const {
  return m_Direction;
}

LinearEquation Ray::getLineEquation() const {
  return m_LineEquation;
}

bool Ray::couldContain(glm::vec2 const& point) const {
  const bool isPointingUpwards = m_Direction.y > 0;
  const bool isPointingRight = m_Direction.x > 0;
  bool result = true;
  result &= isPointingUpwards ? point.y >= m_Origin.y : point.y <= m_Origin.y;
  result &= isPointingRight ? point.x >= m_Origin.x : point.x <= m_Origin.x;
  return result;
}

void Ray::updateEquation() {
  if (m_Direction.x != 0) {  // ray is not vertical
    m_LineEquation.gradient = m_Direction.y / m_Direction.x;
    m_LineEquation.offset = m_Origin.y - m_LineEquation.gradient * m_Origin.x;
  } else {
    m_LineEquation.gradient = m_LineEquation.offset = std::numeric_limits<double>::infinity();
  }
}

}  // namespace math

}  // namespace pool