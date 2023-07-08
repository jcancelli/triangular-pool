#ifndef LINEAR_EQUATION_HPP
#define LINEAR_EQUATION_HPP

#include <ostream>

namespace pool {

namespace math {

struct LinearEquation {
  double gradient;
  double offset = 0.0;
  double operator()(double x) const;
  bool isValid() const;
};

std::ostream& operator<<(std::ostream& os, LinearEquation const& equation);

}  // namespace math

}  // namespace pool

#endif