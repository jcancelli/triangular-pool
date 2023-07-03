#include "linear_equation.hpp"

double LinearEquation::operator()(double x) const {
  return gradient * x + offset;
}