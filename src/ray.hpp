#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec2.hpp>

class Ray {
 private:
  glm::vec2 m_Origin;
  glm::vec2 m_Direction;

 public:
  Ray(glm::vec2 const& origin, glm::vec2 const& direction);
  Ray(glm::vec2 const& direction);
  Ray(Ray const& other);

  void setOrigin(glm::vec2 const& origin);
  glm::vec2 getOrigin() const;
  void setDirection(glm::vec2 const& direction);
  glm::vec2 getDirection() const;
  bool Ray::couldContain(glm::vec2 const& point) const;
};

#endif