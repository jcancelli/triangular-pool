
#include "wall.hpp"

#include <glm/geometric.hpp>
#include <stdexcept>
#include <string>

Wall::Wall(double r1, double r2, double l) : m_Start(0, r1), m_End(l, r2) {
  if ((r1 > 0) == (r2 > 0)) {
    throw std::invalid_argument("r1 and r2 must be on the same side of the x axis");
  }
  updateNormal();
}

Wall::Wall(glm::vec2 const& start, glm::vec2 const& end) : m_Start(start), m_End(end) {
  if ((start.y > 0) == (end.y > 0)) {
    throw std::invalid_argument("start and end must be on the same side of the x axis");
  }
  updateNormal();
}

Wall::Wall(Wall const& other)
    : m_Start(other.m_Start), m_End(other.m_End), m_Normal(other.m_Normal) {
}

bool Wall::isAboveXAxis() const {
  return m_Start.y > 0;  // gives for granted that start and end are on the same side of x axis
}

void Wall::setStart(glm::vec2 const& start) {
  if ((start.y > 0) == (m_End.y > 0)) {
    throw std::invalid_argument("start and end must be on the same side of the x axis");
  }
  m_Start = start;
  updateNormal();
}

glm::vec2 Wall::getStart() const {
  return m_Start;
}

void Wall::setEnd(glm::vec2 const& end) {
  if ((m_Start.y > 0) == (end.y > 0)) {
    throw std::invalid_argument("start and end must be on the same side of the x axis");
  }
  m_End = end;
  updateNormal();
}

glm::vec2 Wall::getEnd() const {
  return m_End;
}

glm::vec2 Wall::getNormal() const {
  return m_Normal;
}

Wall Wall::symmetric(Wall const& wall) {
  return Wall(-wall.m_Start.y, -wall.m_End.y, wall.m_End.x);
}

void Wall::updateNormal() {
  float dx = m_End.x - m_Start.x;
  float dy = m_End.y - m_Start.y;
  m_Normal = glm::normalize(isAboveXAxis() ? glm::vec2(dy, -dx) : glm::vec2(-dy, dx));
}
