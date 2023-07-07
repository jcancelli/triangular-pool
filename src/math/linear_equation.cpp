#include "linear_equation.hpp"

#include <limits>

double LinearEquation::operator()(double x) const {
  return gradient * x + offset;
}

bool LinearEquation::isValid() const {
  return gradient != std::numeric_limits<double>::infinity();
}

std::ostream& operator<<(std::ostream& os, LinearEquation const& equation) {
  return os << "y = " << equation.gradient << " * x + " << equation.offset;
}