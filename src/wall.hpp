#ifndef WALL_HPP
#define WALL_HPP

#include "segment.hpp"

class Wall : public Segment {
 public:
  Wall(double r1, double r2, double l);
  Wall(Wall const& other);

  bool isAboveXAxis() const;
};

#endif