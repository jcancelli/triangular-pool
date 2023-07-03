#ifndef LINEAR_EQUATION_HPP
#define LINEAR_EQUATION_HPP

struct LinearEquation {
  double gradient;
  double offset = 0.0;
  double operator()(double x) const;
};

#endif