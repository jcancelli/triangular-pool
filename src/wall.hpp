#ifndef WALL_HPP
#define WALL_HPP

#include "math/segment.hpp"

namespace pool {

class Wall : public math::Segment {
 public:
  Wall(double r1, double r2, double l);
  Wall(Wall const& other);

  bool isAboveXAxis() const;
};

}  // namespace pool

#endif