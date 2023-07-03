#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <glm/vec2.hpp>
#include <utility>

#include "linear_equation.hpp"

class Segment {
 private:
  glm::vec2 m_A, m_B;
  std::pair<glm::vec2, glm::vec2> m_Normals;
  LinearEquation m_LineEquation;

 public:
  Segment(float x1, float y1, float x2, float y2);
  Segment(glm::vec2 const& a, glm::vec2 const& b);
  Segment(LinearEquation const& equation, float x1, float x2);
  Segment(Segment const& other);

  void setA(glm::vec2 const& a);
  glm::vec2 getA() const;
  void setB(glm::vec2 const& b);
  glm::vec2 getB() const;
  std::pair<glm::vec2, glm::vec2> getNormals() const;
  LinearEquation getLineEquation() const;
  float length() const;

 private:
  void updateNormals();
  void updateEquation();
};

#endif