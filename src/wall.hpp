#ifndef WALL_HPP
#define WALL_HPP

#include <glm/vec2.hpp>

class Wall {
 private:
  glm::vec2 m_Start, m_End;
  glm::vec2 m_Normal;

 public:
  Wall(double r1, double r2, double l);
  Wall(glm::vec2 const& start, glm::vec2 const& end);
  Wall(Wall const& other);

  bool isAboveXAxis() const;
  void setStart(glm::vec2 const& start);
  glm::vec2 getStart() const;
  void setEnd(glm::vec2 const& end);
  glm::vec2 getEnd() const;
  glm::vec2 getNormal() const;

  // returns a new wall symmetrical to the supplied wall about the x-axis
  static Wall symmetric(Wall const& wall);

 private:
  void updateNormal();
};

#endif