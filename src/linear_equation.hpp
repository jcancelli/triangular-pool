#ifndef LINEAR_EQUATION_HPP
#define LINEAR_EQUATION_HPP

struct LinearEquation {
  double gradient;
  double offset;
  double operator()(double x) const;
};

#endif