#ifndef LINEAR_EQUATION_HPP
#define LINEAR_EQUATION_HPP

struct LinearEquation {
  double angularCoef;
  double offset;
  double operator()(double x) const;
};

#endif