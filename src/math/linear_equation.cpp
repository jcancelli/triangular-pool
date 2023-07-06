#include "linear_equation.hpp"

double LinearEquation::operator()(double x) const {
  return gradient * x + offset;
}

std::ostream& operator<<(std::ostream& os, LinearEquation const& equation) {
  return os << "y = " << equation.gradient << " * x + " << equation.offset;
}