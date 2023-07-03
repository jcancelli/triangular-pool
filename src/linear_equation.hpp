#ifndef LINEAR_EQUATION_HPP
#define LINEAR_EQUATION_HPP

#include <ostream>

struct LinearEquation {
  double gradient;
  double offset = 0.0;
  double operator()(double x) const;
};

std::ostream& operator<<(std::ostream& os, LinearEquation const& equation);

#endif