#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec2.hpp>

#include "linear_equation.hpp"

namespace pool {

namespace math {

class Ray {
 private:
  glm::vec2 m_Origin;
  glm::vec2 m_Direction;
  LinearEquation m_LineEquation;

 public:
  Ray(glm::vec2 const& origin, glm::vec2 const& direction);
  Ray(glm::vec2 const& direction);
  Ray(Ray const& other);

  void setOrigin(glm::vec2 const& origin);
  glm::vec2 getOrigin() const;
  void setDirection(glm::vec2 const& direction);
  glm::vec2 getDirection() const;
  LinearEquation getLineEquation() const;
  bool couldContain(glm::vec2 const& point) const;

 private:
  void updateEquation();
};

}  // namespace math

}  // namespace pool

#endif