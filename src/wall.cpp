
#include "wall.hpp"

#include <glm/geometric.hpp>
#include <stdexcept>
#include <string>

namespace pool {

Wall::Wall(double r1, double r2, double l) : Segment::Segment(0, r1, l, r2) {
  if ((r1 > 0) != (r2 > 0)) {
    throw std::invalid_argument("r1 and r2 must be on the same side of the x axis");
  }
}

Wall::Wall(Wall const& other) : Segment::Segment(other.getA(), other.getB()) {
}

bool Wall::isAboveXAxis() const {
  return getA().y > 0;  // gives for granted that start and end are on the same side of x axis
}

}