#include "segment.hpp"

#include <glm/geometric.hpp>
#include <stdexcept>

Segment::Segment(float x1, float y1, float x2, float y2) : m_A(x1, y1), m_B(x2, y2) {
  if (m_A == m_B) {
    throw std::invalid_argument("Cannot create a 0-length segment");
  }
  updateNormals();
  updateEquation();
}

Segment::Segment(glm::vec2 const& a, glm::vec2 const& b) : m_A(a), m_B(b) {
  if (m_A == m_B) {
    throw std::invalid_argument("Cannot create a 0-length segment");
  }
  updateNormals();
  updateEquation();
}

Segment::Segment(LinearEquation const& equation, float x1, float x2)
    : m_A(x1, equation(x1)), m_B(x2, equation(x2)) {
  if (m_A == m_B) {
    throw std::invalid_argument("Cannot create a 0-length segment");
  }
  updateNormals();
  updateEquation();
}

Segment::Segment(Segment const& other)
    : m_A(other.m_A),
      m_B(other.m_B),
      m_Normals(other.m_Normals),
      m_LineEquation(other.m_LineEquation) {
}

void Segment::setA(glm::vec2 const& a) {
  if (a == m_B) {
    throw std::invalid_argument("0-length segment not allowed");
  }
  m_A = a;
}

glm::vec2 Segment::getA() const {
  return m_A;
}

void Segment::setB(glm::vec2 const& b) {
  if (b == m_A) {
    throw std::invalid_argument("0-length segment not allowed");
  }
  m_B = b;
}

glm::vec2 Segment::getB() const {
  return m_B;
}

std::pair<glm::vec2, glm::vec2> Segment::getNormals() const {
  return m_Normals;
}

LinearEquation Segment::getLineEquation() const {
  return m_LineEquation;
}

float Segment::length() const {
  return glm::distance(m_A, m_B);
}

bool Segment::couldContain(glm::vec2 const& point) const {
  const bool isALeftmost = m_A.x < m_B.x;
  const bool isALowest = m_A.y < m_B.y;
  glm::vec2 const& leftmost = isALeftmost ? m_A : m_B;
  glm::vec2 const& rightmost = isALeftmost ? m_B : m_A;
  glm::vec2 const& lowest = isALowest ? m_A : m_B;
  glm::vec2 const& highest = isALowest ? m_B : m_A;
  return point.x >= leftmost.x && point.x <= rightmost.x && point.y >= lowest.y &&
         point.y <= highest.y;
}

void Segment::updateNormals() {
  float dx = m_B.x - m_A.x;
  float dy = m_B.y - m_A.y;
  m_Normals = {glm::normalize(glm::vec2(dy, -dx)), glm::normalize(glm::vec2(-dy, dx))};
}

void Segment::updateEquation() {
  const glm::vec2 direction = m_A.x > m_B.x ? m_A - m_B : m_B - m_A;
  m_LineEquation.gradient = direction.y / direction.x;
  m_LineEquation.offset = m_A.y - m_LineEquation.gradient * m_A.x;
}
